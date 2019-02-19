#include <iostream>
#include <complex>
#include <cstdint>
#include <cmath>

#define PI 3.1415926535
#define NUM_SAMPLES 48128
#define NUM_SAMPLES_PER_FFT 1024
#define NUM_SAMPLES_PER_FFT_FRAME 512
#define MEL_LOWEST_FREQUENCY 300
#define MEL_HIGHEST_FREQUENCY 8000
#define MEL_NUM_FILTERBANKS 26
#define SAMPLING_FREQUENCY 48000
int bits_per_sample = 0;

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
double* window_FFT(complex<double>* input_data, int frame_size, int frame_step, int samplerate);
double** init_mel(double min_frequency, double max_frequency, int num_filterbanks, int FFT_size, int samplerate);
double freq_to_mel(double freq);
double mel_to_freq(double mel);
void generate_filterbank(double* filterbank, double prev_filterbank, double curr_filterbank, double next_filterbank, int FFT_size);
double* calculate_filterbank_energies(double* input_data, double** filters, int num_filterbanks, int FFT_size);

int main()
{
  complex<double> wav_data[NUM_SAMPLES];
  int sampling_frequency = read_wav(wav_data, "2k_test.wav");
  double* power_data = window_FFT(wav_data, NUM_SAMPLES_PER_FFT, NUM_SAMPLES_PER_FFT_FRAME, SAMPLING_FREQUENCY);
  double** filters = init_mel(MEL_LOWEST_FREQUENCY, MEL_HIGHEST_FREQUENCY, MEL_NUM_FILTERBANKS, NUM_SAMPLES_PER_FFT, SAMPLING_FREQUENCY);
  double* filterbank_energies = calculate_filterbank_energies(power_data, filters, MEL_NUM_FILTERBANKS, NUM_SAMPLES_PER_FFT);
  
  for(int i = 0; i < MEL_NUM_FILTERBANKS; i++)
  {
    filterbank_energies[i] = log(filterbank_energies[i]);
    cout << "Filterbank " << i + 1 << " energy: " << filterbank_energies[i] << endl;
  }

  delete[] power_data;
  delete[] filterbank_energies;
  for(int i = 0; i < MEL_NUM_FILTERBANKS; i++){
    // cout << "Filter: " << i << endl;
    // for(int j = 0; j < 256; j++)
    //   cout << filters[i][j] << ", ";
    // cout << endl;
    delete[] filters[i];
  }
  delete[] filters;
  cout << "Program exited normally" << endl;
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
    //cout << ".wav-header has a size of " << bytesRead << endl;
    if(bytesRead > 0)
    {
      cout << "Sample rate: " << wavHeader.sampleRate << endl;
      cout << "Data size: " << wavHeader.subchunk2Size << endl;
      cout << "Bits per sample: " << wavHeader.bitsPerSample << endl;
      bits_per_sample = wavHeader.bitsPerSample;
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
      //cout << "Done reading .wav-file" << endl;
      fclose(wavFile);
      return(wavHeader.sampleRate);
    }
    else
      return(0);
  }
}
double* window_FFT(complex<double>* input_data, int frame_size, int frame_step, int samplerate)
{
  //cout << "Started window FFT" << endl;
  complex<double>* data_frame = new complex<double>[frame_size];
  double* FFT_ABS = new double[NUM_SAMPLES];
  double hamming_window [frame_size];
  // Slide the frame along the array of samples, frame=1024, frame_step = 512
  // Calculate Hamming-window coefficients
  for(int i = 0; i < frame_size; i++){
    hamming_window[i] = 0.54 - 0.46 * cos(2*PI*i/(frame_size-1));
  }
  for(int frame = 0; frame < (NUM_SAMPLES - NUM_SAMPLES_PER_FFT_FRAME); frame += frame_step)
  {
    // Fill the window array with windowed FFT samples
    for(int i = 0; i < frame_size; i++)
    {
      // Perform Hamming-windowing while copying sample. Voice-data is only real, so ignore the imaginary part
      data_frame[i] = input_data[i].real() * hamming_window[i];
      // TODO: Find Signal-to-noise ratio
      if(frame == 0)
        cout << data_frame[i].real() << ", ";
    }
    FFT(data_frame, frame_size);
    if(frame == 0)
      cout << endl;
    // Calculate the periodogram-based power spectral estimate of the first half of the signal
    for(int j = 0; j < frame_size/2; j++){
      FFT_ABS[j + frame] = pow((data_frame[j].real() * data_frame[j].imag()),2) / frame_size;
      //FFT_ABS[j + frame] = floor((frame_size + 1) * FFT_ABS[j + frame] / (samplerate));
      FFT_ABS[j + frame] = floor(FFT_ABS[j + frame] / (samplerate));
      if(frame == 0)
        cout << FFT_ABS[j + frame] << ", ";
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
    cout << "Filterbank " << i << ": ";
    cout << "Mel: " << filterbanks[i] << ", ";
    // Convert back to frequency
    filterbanks[i] = mel_to_freq(filterbanks[i]);
    cout << "Freq: " << filterbanks[i] << ", ";
    // Round frequencies to a precision we have
    filterbanks[i] = floor((FFT_size + 1) * filterbanks[i] / samplerate);
    cout << "Rounded: " << filterbanks[i] << endl;
    // Create filterbank filters
    if((i > 1) && (i < (num_filterbanks + 2)))
      generate_filterbank(filterbank_filters[i-2], filterbanks[i-2], filterbanks[i-1], filterbanks[i], FFT_size);
  }
  delete[] filterbanks;
  return(filterbank_filters);

  cout << "Program exited successfully" << endl;
}
void generate_filterbank(double* filterbank, double prev_filterbank, double curr_filterbank, double next_filterbank, int FFT_size){
  // Use i to cycle through the arrays, use j to increment the step value
  int i = 0;
  int j = 0;
  double step = 1/(curr_filterbank-prev_filterbank);
    for(i = 0; i < prev_filterbank; i++)
      filterbank[i] = 0;
    for(; i < curr_filterbank; i++){
      filterbank[i] = step * j;
      j++;
    }
    j = 0;
    for(; i < next_filterbank; i++){
      filterbank[i] = 1 - (step * j);
      j++;
    }
    for(; i < FFT_size/2; i++)
      filterbank[i] = 0;
}
double* calculate_filterbank_energies(double* input_data, double** filters, int num_filterbanks, int FFT_size)
{
  double* filterbank_energies = new double[num_filterbanks];
  // Run filters over each frame. Frames are 512, as are the filters.Add the result of all frames for each iteration of the filterbank filter
  for(int filterbank = 0; filterbank < num_filterbanks; filterbank++)
  {
    filterbank_energies[filterbank] = 0;
    for(int FFT_frame = 0; FFT_frame < NUM_SAMPLES; FFT_frame += FFT_size / 2)
    {
      for(int i = 0; i < FFT_size / 2; i++)
      {
        filterbank_energies[filterbank] += input_data[i] * filters[filterbank][i];
      }
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
