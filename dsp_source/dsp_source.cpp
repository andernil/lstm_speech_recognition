#include <iostream>
#include <complex>
#include <cstdint>
#include <cmath>
#include <fstream>
#include <bitset>
#include <string>

#define PI 3.1415926535
#define NUM_SAMPLES 16000
#define NUM_SAMPLES_PER_FFT 1024 // 32 ms per frame
#define FRAME_STEP_LENGTH 128 // 16 ms step length
#define NUM_SAMPLES_PER_FRAME NUM_SAMPLES_PER_FFT / 2
#define NUM_FRAMES (NUM_SAMPLES - NUM_SAMPLES_PER_FFT) / FRAME_STEP_LENGTH + 1
#define NUM_SAMPLES_POST_FFT NUM_SAMPLES_PER_FFT / 2
#define MEL_LOWEST_FREQUENCY 300
#define MEL_HIGHEST_FREQUENCY 8000
#define MEL_NUM_FILTERBANKS 80
#define SAMPLING_FREQUENCY 16000
#define NUM_MFCC_VALUES (MEL_NUM_FILTERBANKS / 2) - 1
#define LOW_VALUE_BOUND 1e-10

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
double* window_FFT(complex<double>* input_data, int num_samples, int frame_size, int frame_step, int num_frames, int peak_value);
double** init_mel(double min_frequency, double max_frequency, int num_filterbanks, int FFT_size, int samplerate);
void generate_filterbank(double* filterbank, double prev_filterbank, double curr_filterbank, double next_filterbank, int FFT_size);
double** calculate_filterbank_energies(double* input_data, double** filters, int num_filterbanks, int num_frames, int frame_size, int FFT_size);
double freq_to_mel(double freq);
double mel_to_freq(double mel);

int main(int argc, char* argv[])
{
   if(argc != 3)
   {
      cout << "The program requries two input arguments: input file directory and input .wav-file" << endl;
      return(0);
   }
  // Current directory
  string curr_dir = argv[1];
  
  // Set input file
  string input_file = curr_dir + "/" + argv[2];
  char input_char_array [input_file.size() + 1];
  input_file.copy(input_char_array, input_file.size() + 1);
  input_char_array[input_file.size()] = '\0';
  
  // Store the MFCC-data for testing, first value is the number of MFCC-values for each frame
  size_t without_extension = input_file.find_last_of(".");
  size_t without_root = input_file.find_last_of("/");
  string output_file = curr_dir + "/Mels/" + input_file.substr(without_root + 1, without_extension + 1);
  without_extension = output_file.find_last_of(".");
  output_file = output_file.substr(0, without_extension) + ".dat";

  ofstream Mels;
  Mels.open(output_file);
  Mels << MEL_NUM_FILTERBANKS << "\n";

  int num_frames = NUM_FRAMES;
  int num_samples_per_fft = NUM_SAMPLES_PER_FFT;
  int num_samples_post_framing = num_frames * num_samples_per_fft / 2;

  complex<double> wav_data[NUM_SAMPLES];
  int peak_value = read_wav(wav_data, input_char_array);

  double* power_data = window_FFT(wav_data, NUM_SAMPLES, NUM_SAMPLES_PER_FFT, FRAME_STEP_LENGTH, NUM_FRAMES, peak_value);

  double** filters = init_mel(MEL_LOWEST_FREQUENCY, MEL_HIGHEST_FREQUENCY, MEL_NUM_FILTERBANKS, NUM_SAMPLES_PER_FFT, SAMPLING_FREQUENCY);
  double** filterbank_energies = calculate_filterbank_energies(power_data, filters, MEL_NUM_FILTERBANKS, NUM_FRAMES, NUM_SAMPLES_PER_FRAME, NUM_SAMPLES_PER_FFT);
  // Write datain the style (FRAMES, FILTERBANKS)
  for(int i = 0; i < NUM_FRAMES; i++)
  {
    for(int j = 0; j < MEL_NUM_FILTERBANKS; j++)
    {
      Mels << filterbank_energies[i][j] << "\n";
    }
  }
  for(int i = 0; i < MEL_NUM_FILTERBANKS; i++){
    delete[] filters[i];
    delete[] filterbank_energies[i];
  }
  delete[] filterbank_energies;
  delete[] filters;
  delete[] power_data;

  filterbank_energies = nullptr;
  filters = nullptr;
  power_data = nullptr;

  Mels.close();

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
  int peak_value = 0;
  int peak_neg_value = 0;
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
      long bytes = wavHeader.bitsPerSample/8;
      long buffsize= wavHeader.subchunk2Size/bytes;
      if(wavHeader.bitsPerSample == 32)
      {
        int32_t* audiobuf = new int32_t[buffsize];
        fread(audiobuf,bytes,buffsize,wavFile);
        for(int i = 0; i < buffsize; i++){
          data_array[i] = audiobuf[i];
          if(audiobuf[i] > peak_value)
            peak_value = audiobuf[i];
          else if(audiobuf[i] < peak_neg_value)
            peak_neg_value = audiobuf[i];
        }
        delete[] audiobuf;
        audiobuf <= nullptr;
      }
      else
      {
        int16_t* audiobuf = new int16_t[buffsize];
        fread(audiobuf,bytes,buffsize,wavFile);
        for(int i = 0; i < buffsize; i++){
          data_array[i] = audiobuf[i];
          if(audiobuf[i] > peak_value)
            peak_value = audiobuf[i];
          else if(audiobuf[i] < peak_neg_value)
            peak_neg_value = audiobuf[i];
        }
        delete[] audiobuf;
        audiobuf = nullptr;
      }
      fclose(wavFile);
      if(peak_value < abs(peak_neg_value))
        peak_value = abs(peak_neg_value);
      return(peak_value);
    }
    else
      cout << "Unable to read wav data" << endl;
      return(0);
  }
}
double* window_FFT(complex<double>* input_data, int num_samples, int frame_size, int frame_step, int num_frames, int peak_value)
{
  int num_samples_post_framing = frame_size * num_frames / 2;
  complex<double>* data_frame = new complex<double>[frame_size];
  double* FFT_ABS = new double[num_samples_post_framing];
  double hamming_window [frame_size];
  double to_FFT[frame_size] = {0};
  // Scale the input data within the range +/- 1 and shift 8 bits to avoid overflow
  double scaling = peak_value * (1 << 9); //8
  // Slide the frame along the array of samples, frame=1024, frame_step = 512
  // Calculate Hamming-window coefficients
  for(int i = 0; i < frame_size; i++){
    hamming_window[i] = 0.54 - 0.46 * cos(2*PI*i/(frame_size-1));
  }
  for(int frame = 0; frame < num_frames; frame++)
    {
      // Fill the window array with windowed FFT samples
      for(int i = 0; i < frame_size; i++)
      {
        // Perform Hamming-windowing while copying sample. Voice-data is only real, so ignore the imaginary part
        data_frame[i] = input_data[i + (frame * frame_step)].real() * hamming_window[i] / scaling; //23 for match
        to_FFT[i] = data_frame[i].real();
      }
      FFT(data_frame, frame_size);
      // Calculate the periodogram-based power spectral estimate of the first half of the signal
      for(int j = 0; j < frame_size/2; j++){
        FFT_ABS[j + (frame * frame_size/2)] = pow(abs(data_frame[j]),2) / frame_size;
        if(abs(data_frame[j].real()) >= 2 || abs(data_frame[j].imag()) >= 2)
          cout << "Large number: " << FFT_ABS[j + (frame * frame_size/2)] << ". Real: " << data_frame[j].real() << ". Imag: " << data_frame[j].imag() << endl;
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
    // Convert back to frequency
    filterbanks[i] = mel_to_freq(filterbanks[i]);
    // Round frequencies to a precision we have
    filterbanks[i] = floor((FFT_size + 1) * filterbanks[i] / samplerate);
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
  double filter_avgs = 0;
  // Allocate memory for the filterbanks
  double** filterbank_energies = new double*[num_frames];
  for(int frame = 0; frame < num_frames; frame++){
    filterbank_energies[frame] = new double[num_filterbanks];
    for(int filterbank = 0; filterbank < num_filterbanks; filterbank++)
      filterbank_energies[frame][filterbank] = 0;
  }
  // Run filters over each frame. Frames are 512, as are the filters.
  for(int FFT_frame = 0; FFT_frame < num_frames; FFT_frame++)
  {
    // Calculate sum for each filterbank for each frame
    for(int filterbank = 0; filterbank < num_filterbanks; filterbank++)
    {
      for(int power_data = 0; power_data < frame_size; power_data++)
      {
        filterbank_energies[FFT_frame][filterbank] += input_data[power_data + (FFT_frame * frame_size)] * filters[filterbank][power_data];
      }
      if(filterbank_energies[FFT_frame][filterbank] == 0)
        filterbank_energies[FFT_frame][filterbank] = LOW_VALUE_BOUND;
    }
  }

  // Calculate average of mel logs
  double num_filter_values = double(NUM_FRAMES) * double(MEL_NUM_FILTERBANKS);
  for(int i = 0; i < NUM_FRAMES; i++){
    for(int j = 0; j < MEL_NUM_FILTERBANKS; j++){
      filterbank_energies[i][j] = 20*log10(filterbank_energies[i][j]);
      filter_avgs += filterbank_energies[i][j]/(num_filter_values);
    }
  }
  // Subtract average from all log values
  for(int i = 0; i < NUM_FRAMES; i++){
    for(int j = 0; j < MEL_NUM_FILTERBANKS; j++){
      filterbank_energies[i][j] -= filter_avgs;
    }
  }
  return(filterbank_energies);
}
double freq_to_mel(double freq){
  return(1125 * log(1 + freq/700));

}
double mel_to_freq(double mel){
  return(700 * (exp(mel/1125) - 1));
}
