#include <iostream>
#include <complex>
#include <cstdint>

#define PI 3.1415926535
#define NUM_SAMPLES 49152
#define NUM_SAMPLES_PER_FFT 2048

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

int main()
{
  complex<double> wav_data[NUM_SAMPLES];
  int wav_data_length = read_wav(wav_data, "1k_test.wav");
  for(int i = 0; i < NUM_SAMPLES; i++)
    //cout << wav_data[i].real() << ", ";
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
    cout << ".wav-header has a size of " << bytesRead << endl;
    if(bytesRead > 0)
    {
      cout << "Sampling rate: " << wavHeader.sampleRate << endl;
      cout << "Data size: " << wavHeader.subchunk2Size << endl;
      cout << "Bits per sample: " << wavHeader.bitsPerSample << endl;
      long bytes = wavHeader.bitsPerSample/8;
      long buffsize= wavHeader.subchunk2Size/bytes;
      if(wavHeader.bitsPerSample == 32)
      {
        cout << "Allocating 32-bit values" << endl;
        int32_t* audiobuf = new int32_t[buffsize];
        fread(audiobuf,bytes,buffsize,wavFile);
        for(int i = 0; i < buffsize; i++)
          data_array[i] = audiobuf[i];
        delete[] audiobuf;
        audiobuf = nullptr;
      }
      else
      {
        cout << "Allocating 16-bit values" << endl;
        int16_t* audiobuf = new int16_t[buffsize];
        fread(audiobuf,bytes,buffsize,wavFile);
        for(int i = 0; i < buffsize; i++)
          data_array[i] = audiobuf[i];
        delete[] audiobuf;
        audiobuf = nullptr;
      }
      cout << "Buffsize: " << buffsize << endl;
      cout << "Num samples: " << buffsize << endl;
      cout << "Done reading .wav-file" << endl;
      fclose(wavFile);
      return(buffsize);
    }
    else
      return(0);
  }
}
