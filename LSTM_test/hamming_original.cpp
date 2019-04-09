#include <iostream>
#include <complex>
#include <cstdint>
#include <cmath>
#include <fstream>
#include <bitset>
#include <string>

#define PI 3.1415926535
#define NUM_SAMPLES 16000 // Must be a log2-number // Old: 16384
#define NUM_SAMPLES_PER_FFT 1024 // 32 ms per frame old: 512
#define NUM_SAMPLES_PER_FFT_FRAME_STEP 128 // 16 ms step length old:256
#define NUM_FRAMES NUM_SAMPLES/NUM_SAMPLES_PER_FFT_FRAME_STEP - 1
#define NUM_SAMPLES_POST_FFT NUM_SAMPLES_PER_FFT / 2
#define NUM_SAMPLES_POST_FRAMING NUM_FRAMES * NUM_SAMPLES_PER_FFT / 2 
#define MEL_LOWEST_FREQUENCY 300
#define MEL_HIGHEST_FREQUENCY 8000
#define MEL_NUM_FILTERBANKS 80 //old: 16
#define SAMPLING_FREQUENCY 16000
#define NUM_MFCC_VALUES (MEL_NUM_FILTERBANKS / 2) - 1
#define LOW_VALUE_BOUND 1e-18

using namespace std;

typedef struct WAV_HEADER{
    unsigned char riff_header[4];
    uint32_t chunkSize;
    unsigned char wave_header[4];
    unsigned char fmt_header[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    unsigned char subchunk2Id[4];
    uint32_t subchunk2Size;
} wav_hdr;

void separate(complex<double>* input_data, int num_samples);
void FFT(complex<double>* input_data, int num_samples);
int read_wav(complex<double>* data_array, const char* filename);
double* window_FFT(complex<double>* input_data, int num_samples, int frame_size, int frame_step, int num_frames);
double** init_mel(double min_frequency, double max_frequency, int num_filterbanks, int FFT_size, int samplerate);
void generate_filterbank(double* filterbank, double prev_filterbank, double curr_filterbank, double next_filterbank, int FFT_size);
double** calculate_filterbank_energies(double* input_data, double** filters, int num_filterbanks, int num_frames, int frame_sizefrom, int FFT_size);
double freq_to_mel(double freq);
double mel_to_freq(double mel);

int main(int argc, char* argv[])
{
  // Current directory
  string curr_dir = argv[1];
  
  // Set input file
  string input_file = curr_dir + "/" + argv[2];
  char input_char_array [input_file.size() + 1];
  input_file.copy(input_char_array, input_file.size() + 1);
  input_char_array[input_file.size()] = '\0';
  // Store the MFCC-data for testing, first value is the number of MFCC-values for each frame
  
  ofstream MFCC;
  size_t without_extension = input_file.find_last_of(".");
  size_t without_root = input_file.find_last_of("/");
  string output_file =  curr_dir + "/MFCC/" + input_file.substr(without_root + 1, without_extension + 1);
  without_extension = output_file.find_last_of(".");
  output_file = output_file.substr(0, without_extension) + ".dat";
  MFCC.open(output_file);
  MFCC << NUM_MFCC_VALUES << "\n";

  int num_frames = NUM_FRAMES;
  int num_samples_per_fft = NUM_SAMPLES_PER_FFT;
  int num_samples_post_framing = num_frames * num_samples_per_fft / 2;

  complex<double> wav_data[NUM_SAMPLES];
  int sampling_frequency = read_wav(wav_data, input_char_array);
  //if(sampling_frequency == 0)
  //cout << "Error reading .wav-file: " << curr_dir + "/" + argv[2]  << endl;
  double* power_data = window_FFT(wav_data, NUM_SAMPLES, NUM_SAMPLES_PER_FFT, NUM_SAMPLES_PER_FFT_FRAME_STEP, NUM_FRAMES);
  double** filters = init_mel(MEL_LOWEST_FREQUENCY, MEL_HIGHEST_FREQUENCY, MEL_NUM_FILTERBANKS, NUM_SAMPLES_PER_FFT, SAMPLING_FREQUENCY);
  double** MFCC_energies = calculate_filterbank_energies(power_data, filters, MEL_NUM_FILTERBANKS, NUM_FRAMES, NUM_SAMPLES_PER_FFT_FRAME_STEP, NUM_SAMPLES_PER_FFT);
  
  for(int i = 0; i < NUM_MFCC_VALUES; i++)
  {
    for(int j = 0; j < NUM_FRAMES; j++)
    {
      MFCC << MFCC_energies[i][j] << "\n";
    }
  }

  for(int i = 0; i < MEL_NUM_FILTERBANKS; i++){
    delete[] filters[i];
   }
  for(int i = 0; i < NUM_MFCC_VALUES; i++)
    delete[] MFCC_energies[i];
  delete[] MFCC_energies;
  delete[] filters;
  delete[] power_data;

  MFCC_energies = nullptr;
  filters = nullptr;
  power_data = nullptr;

  MFCC.close();

  //cout << "Program exited normally" << endl;
  cout << "Generated " << output_file << endl;
  return(0);
}


void separate (complex<double>* input_data, int num_samples)
{
  complex<double>* temp_buffer = new complex<double>[num_samples];
  //Copy all odd elements to temp buffer
  for(int i = 0; i < num_samples/2; i++)
    temp_buffer[i] = input_data[i*2+1];
  //Copy all even elements to lower half of input_data
  for(int i = 0; i < num_samples/2; i++)
    input_data[i] = input_data[i*2];
  //Copy all odd elements from buffer to upper half of input_data
  for(int i = 0; i < num_samples/2; i++)
    input_data[i+num_samples/2] = temp_buffer[i];
  //Delete the allocated temp buffer
  delete[] temp_buffer;
  temp_buffer = nullptr;
}

void FFT(complex<double>* input_data, int num_samples)
{
  if(num_samples < 2)
    asm("NOP");
  else
  {
    // Separate all even numbers to lower half, odd to upper half
    separate(input_data, num_samples);
    //Recurse even items
    FFT(input_data, num_samples/2);
    //Recurse odd times
    FFT(input_data + num_samples/2, num_samples/2);
    for(int i = 0; i < num_samples/2; i++)
    {
      complex<double> even = input_data[i];
      complex<double> odd = input_data[i+num_samples/2];
      complex<double> twiddle_factor = exp(complex<double>(0, -2 * PI * i/num_samples));
      input_data[i] = even + twiddle_factor * odd;
      input_data[i + num_samples/2] = even - twiddle_factor * odd;
    }
  }
}
int read_wav(complex<double>* data_array, const char* filename)
{
  wav_hdr wavHeader;
  int headerSize = sizeof(wav_hdr);
  FILE* wavFile = fopen(filename, "r");
  if(wavFile == nullptr)
  {
    cout << "Invalid filename" << endl;
    return(0);
  }
  else
  {
    size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
    if(bytesRead > 0)
    {
      //cout << "Sample rate: " << wavHeader.sampleRate << endl;
      //cout << "Bits per sample: " << wavHeader.bitsPerSample << endl;
      //cout << "Num samples: " << wavHeader.subchunk2Size/(wavHeader.numChannels * wavHeader.bitsPerSample/8) << endl;
      long bytes = wavHeader.bitsPerSample/8;
      long buffsize= wavHeader.subchunk2Size/bytes;
      if(wavHeader.bitsPerSample == 32)
      {
        int32_t* audiobuf = new int32_t[buffsize];
        fread(audiobuf,bytes,buffsize,wavFile);
        for(int i = 0; i < buffsize; i++)
          data_array[i] = audiobuf[i];
        delete[] audiobuf;
        audiobuf = nullptr;
      }
      else
      {
        int16_t* audiobuf = new int16_t[buffsize];
        fread(audiobuf,bytes,buffsize,wavFile);
        for(int i = 0; i < buffsize; i++){
          data_array[i] = audiobuf[i];
        }
        delete[] audiobuf;
        audiobuf = nullptr;
      }
      fclose(wavFile);
      return(wavHeader.sampleRate);
    }
    else
      cout << "Unable to read wav data" << endl;
      return(0);
  }
} 
double* window_FFT(complex<double>* input_data, int num_samples, int frame_size, int frame_step, int num_frames)
{
  int num_samples_post_framing = frame_size * num_frames / 2;
  complex<double>* data_frame = new complex<double>[frame_size];
  double* FFT_ABS = new double[num_samples_post_framing];
  double hamming_window [frame_size];
  double to_FFT[frame_size] = {0};
  double scaling = (1 << 23) - 1;

  // Slide the frame along the array of samples, frame=1024, frame_step = 512
  // Calculate Hamming-window coefficients
  for(int i = 0; i < frame_size; i++){
    hamming_window[i] = 0.54 - 0.46 * cos(2*PI*i/(frame_size-1));
  }
  for(int frame = 0; frame < (num_samples - frame_size); frame += frame_step)
    {
      //cout << "Calculating from " << frame << " to " << frame + frame_step << endl;
      // Fill the window array with windowed FFT samples
      for(int i = 0; i < frame_size; i++)
      {
        // Perform Hamming-windowing while copying sample. Voice-data is only real, so ignore the imaginary part
        data_frame[i] = input_data[i + frame].real() * hamming_window[i] / ((1 << 23 ) - 1); //23 for match
        to_FFT[i] = data_frame[i].real();
      }
      FFT(data_frame, frame_size);
      // Calculate the periodogram-based power spectral estimate of the first half of the signal
      for(int j = 0; j < frame_size/2; j++){
        FFT_ABS[j + frame] = pow(abs(data_frame[j]),2) / frame_size;
        if(FFT_ABS[j] > 1)
          cout << "Large number: " << FFT_ABS[j] << ". Real: " << data_frame[j].real() << ". Imag: " << data_frame[j].imag() << endl;
        //if(frame == 58*NUM_SAMPLES_PER_FFT_FRAME){
        //cout << "Pre hamming: " << input_data[j + frame]/scaling << endl;
        //cout << "To FFT: " << to_FFT[j] << " and " << to_FFT[j + frame_step] << endl;
        //cout << "From FFT: " << data_frame[j] << endl;
    		//cout << j << ": " << "Abs: " << FFT_ABS[j + frame] << endl;
        // }
        //      cout << FFT_ABS[j + frame] << endl;
      }
    }
  delete[] data_frame;
  return(FFT_ABS);
}

double** init_mel(double min_frequency, double max_frequency, int num_filterbanks, int FFT_size, int samplerate){
  double min_mel = freq_to_mel(min_frequency);
  double max_mel = freq_to_mel(max_frequency);
  double filterbank_step = (max_mel - min_mel) / (num_filterbanks + 1);
  // The number of filterbanks is always n+2
  double* filterbanks = new double[num_filterbanks + 2];
  double** filterbank_filters = new double*[num_filterbanks];
  for(int i = 0; i < num_filterbanks; i++)
    filterbank_filters[i] = new double[FFT_size/2];
  for(int i = 0; i < num_filterbanks + 2; i++){
    filterbanks[i] = min_mel + filterbank_step * i;
    //cout << "Filterbank " << i << ": ";
    //cout << "Mel: " << filterbanks[i] << ", ";
    // Convert back to frequency
    filterbanks[i] = mel_to_freq(filterbanks[i]);
    //cout << "Freq: " << filterbanks[i] << ", ";
    // Round frequencies to a precision we have
    filterbanks[i] = floor((FFT_size + 1) * filterbanks[i] / samplerate);
    //cout << "Rounded: " << filterbanks[i] << endl;
    // Create filterbank filters
    if((i > 1) && (i < (num_filterbanks + 2)))
    {
      generate_filterbank(filterbank_filters[i-2], filterbanks[i-2], filterbanks[i-1], filterbanks[i], FFT_size);
    }
  }
  delete[] filterbanks;
  filterbanks = nullptr;
  return(filterbank_filters);
}
void generate_filterbank(double* filterbank, double prev_filterbank, double curr_filterbank, double next_filterbank, int FFT_size){
  // Use i to cycle through the arrays, use j to increment the step value
  int i = 0;
  int j = 0;
  double up_step = 1/(curr_filterbank-prev_filterbank);
  double down_step = 1/(next_filterbank - curr_filterbank);
    for(i = 0; i < prev_filterbank; i++)
      filterbank[i] = 0;
    for(; i < curr_filterbank; i++){
      filterbank[i] = up_step * j;
      j++;
    }
    j = 0;
    for(; i < next_filterbank; i++){
      filterbank[i] = 1 - (down_step * j);
      j++;
    }
    for(; i < FFT_size/2; i++)
      filterbank[i] = 0;
}
double** calculate_filterbank_energies(double* input_data, double** filters, int num_filterbanks, int num_frames, int frame_size, int FFT_size)
{
  int lowest_val = 1;
  // Allocate memory for the filterbanks
  double** filterbank_energies = new double*[num_frames];
  for(int frame = 0; frame < num_frames; frame++){
    filterbank_energies[frame] = new double[num_filterbanks];
    for(int filterbank = 0; filterbank < num_filterbanks; filterbank++)
      filterbank_energies[frame][filterbank] = 0;
  }
  double** MFCC_energies = new double*[NUM_MFCC_VALUES];
  for(int MFCC_bank = 0; MFCC_bank < NUM_MFCC_VALUES; MFCC_bank++){
    MFCC_energies[MFCC_bank] = new double[num_frames];
    for(int frame = 0; frame < num_frames; frame++)
      MFCC_energies[MFCC_bank][frame] = 0;
  }

  // Allocate memory for DCT buffer. Re-use FFT for calculating DCT
  int num_DCT_energies = 4 * num_filterbanks;
  complex<double>* DCT_energies = new complex<double>[num_DCT_energies];
  for(int i = 0; i < num_DCT_energies; i++)
    DCT_energies[i] = 0;

  // Run filters over each frame. Frames are 512, as are the filters.
  for(int FFT_frame = 0; FFT_frame < num_frames; FFT_frame++)
  {
    // Calculate sum for each filterbank for each frame
    for(int filterbank = 0; filterbank < num_filterbanks; filterbank++)
    {
      for(int power_data = 0; power_data < frame_size; power_data++)
      {
        filterbank_energies[FFT_frame][filterbank] += input_data[power_data + (FFT_frame * frame_size)] * filters[filterbank][power_data];
        //if(FFT_frame == 58)
        //cout << "Filterbank: " << filterbank << ": " << filterbank_energies[58][filterbank] << endl;
      //   if(FFT_frame == 0 && filterbank == 7)
      //     cout << "Power data " << power_data << ": " << input_data[power_data] << endl;
      //   // if(input_data[power_data] > 1 && FFT_frame == 0){
      //   // 	cout << "Very large number:" << endl;
      //   // 	cout << "Input: " << input_data[power_data] << endl;
      //   // 	cout << "Filter value: " << filters[filterbank][power_data] << endl;
      //   // 	cout << "Output energy: " << filterbank_energies[0][7] << endl;
      //   // }
      }
      if(filterbank_energies[FFT_frame][filterbank] == 0)
        filterbank_energies[FFT_frame][filterbank] = LOW_VALUE_BOUND;
      //cout << "Filterbank: " << filterbank << ": " << filterbank_energies[FFT_frame][filterbank] << endl;
    }
    // Create DCT input array
    int j = 0;
    for(int i = 0; i < num_DCT_energies; i++)
    {
      if(i < num_DCT_energies/2)
      {
        if((i % 2 != 0)){
          DCT_energies[i] = DCT_energies[num_DCT_energies - i] = log(filterbank_energies[FFT_frame][j]) / (1024);
          //DCT_energies[i] = DCT_energies[num_DCT_energies - i] = test_input[j];
          // if(FFT_frame == 0){
          //cout << "Energy " << j << " pre-scaling: " << filterbank_energies[FFT_frame][j] << endl;
          //           cout << "Filterbank energy log" << j << ": " << (log(filterbank_energies[FFT_frame][j])) << endl;
          //cout << "Filterbank log energy " << j << ": " << DCT_energies[i] << endl;
          // }
          j++;
        }
      }
    }

    // Perform DCT for the current frame and copy the result back to filterbank_energies
    //for(int i = 0; i < 64; i++)
      //  cout << DCT_energies[i] << ", ";
    FFT(DCT_energies, 64);
    //for(int i = 0; i < 64; i++)
    //cout << DCT_energies[i] << endl;
    for(int MFCC_value = 0; MFCC_value < num_filterbanks; MFCC_value++){
      if((MFCC_value > 0 && MFCC_value < 8)){
        MFCC_energies[MFCC_value - 1][FFT_frame] = DCT_energies[MFCC_value].real();
      }
    }
  }
  //cout << "Done performing MFCC" << endl;
  for(int i = 0; i < MEL_NUM_FILTERBANKS; i++){
    delete[] filterbank_energies[i];
  }
  delete[] filterbank_energies;
  delete[] DCT_energies;
  filterbank_energies = nullptr;
  DCT_energies = nullptr;
  return(MFCC_energies);
}

double freq_to_mel(double freq){
  return(1125 * log(1 + freq/700));

}
double mel_to_freq(double mel){
  return(700 * (exp(mel/1125) - 1));
}