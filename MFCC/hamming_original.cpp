#include "hamming_original.h"
#include <iostream>

#define PI 3.1415926535

#define MEL_LOWEST_FREQUENCY 300
#define MEL_HIGHEST_FREQUENCY 8000
#define MEL_NUM_FILTERBANKS 16
#define SAMPLING_FREQUENCY 48000

bool direction = 0;

using namespace std;
void read_FFT_data(status_t* status_in, bool* ovflo, cmpxDataOut out[FFT_LENGTH], cmpxDataOut from_FFT[FFT_LENGTH]);
void write_FFT_data(bool direction, config_t* fft_config, cmpxDataIn in[FFT_LENGTH], cmpxDataIn to_FFT[FFT_LENGTH]);
void FFT(complex<data_in_t> in[FFT_LENGTH], complex<data_out_t> out[FFT_LENGTH], bool direction, bool* ovflo);
void window_FFT(cmpxDataIn input_data[NUM_SAMPLES], data_out_t output_data[NUM_SAMPLES_POST_FRAMING]);
double** init_mel(double min_frequency, double max_frequency, int num_filterbanks, int FFT_size, int samplerate);
void generate_filterbank(double* filterbank, double prev_filterbank, double curr_filterbank, double next_filterbank, int FFT_size);
double** calculate_filterbank_energies(double* input_data, double** filters, int num_filterbanks, int num_frames, int frame_size, int FFT_size);
double freq_to_mel(double freq);
double mel_to_freq(double mel);

void MFCC_main(cmpxDataIn wav_data[NUM_SAMPLES], data_out_t output_data[NUM_SAMPLES_POST_FRAMING], int sampling_frequency)
{
	cout << "In main" << endl;
  window_FFT(wav_data, output_data);
  /*double** filters = init_mel(MEL_LOWEST_FREQUENCY, MEL_HIGHEST_FREQUENCY, MEL_NUM_FILTERBANKS, NUM_SAMPLES_PER_FFT, SAMPLING_FREQUENCY);
  double** filterbank_energies = calculate_filterbank_energies(power_data, filters, MEL_NUM_FILTERBANKS, NUM_FRAMES, NUM_SAMPLES_PER_FFT_FRAME_STEP, NUM_SAMPLES_PER_FFT);

  for(int i = 0; i < MEL_NUM_FILTERBANKS; i++){
    delete[] filters[i];
   }
  delete[] filters;
  delete[] power_data;

  */
}

void write_FFT_data(bool direction, config_t* fft_config, cmpxDataIn in[FFT_LENGTH], cmpxDataIn to_FFT[FFT_LENGTH])
{
	fft_config->setDir(direction);
	//fft_config->setSch(0x2AB); // For pipelined
	fft_config->setSch(0x55556); //for Radix2
	fft_config->setNfft(10);
	int i;
	for(i = 0; i < FFT_LENGTH; i++)
		to_FFT[i] = in[i];
}
void read_FFT_data(status_t* status_in, bool* ovflo, cmpxDataOut out[FFT_LENGTH], cmpxDataOut from_FFT[FFT_LENGTH])
{
	int i;
	for(i = 0; i < FFT_LENGTH; i++){
		out[i] = from_FFT[i];
	}
	*ovflo = status_in->getOvflo() & 0x1;
}

void FFT(complex<data_in_t> in[FFT_LENGTH], complex<data_out_t> out[FFT_LENGTH], bool direction, bool* ovflo)
{
#pragma HLS interface ap_hs port=direction
//#pragma HLS interface ap_fifo port=x_in
//#pragma HLS interface ap_fifo port=x_out
#pragma HLS interface ap_fifo depth=1 port=ovflo
#pragma HLS interface ap_fifo depth=FFT_LENGTH port=in,out
#pragma HLS data_pack variable=in
#pragma HLS data_pack variable=out
#pragma HLS dataflow
	config_t FFT_config1;
	status_t FFT_status1;
	complex<data_in_t> x_in[FFT_LENGTH];
	complex<data_out_t> x_out[FFT_LENGTH];

	write_FFT_data(direction, &FFT_config1, in, x_in);
	hls::fft<FFT_params>(x_in, x_out, &FFT_status1, &FFT_config1);
	read_FFT_data(&FFT_status1, ovflo, out, x_out);
}

void window_FFT(cmpxDataIn input_data[NUM_SAMPLES], data_out_t output_data[NUM_SAMPLES_POST_FRAMING])
{
	int frame_size = NUM_SAMPLES_PER_FFT;
	int frame_step = NUM_SAMPLES_PER_FFT_FRAME_STEP;
	int num_samples = NUM_SAMPLES;
	bool* overflow;
  cmpxDataIn data_frame [NUM_SAMPLES_PER_FFT];
  data_in_t hamming_window [NUM_SAMPLES_PER_FFT];
  static cmpxDataIn to_FFT [NUM_SAMPLES_PER_FFT];
  static cmpxDataOut from_FFT [NUM_SAMPLES_PER_FFT];
  cout << "Declared variables" << endl;
  // Slide the frame along the array of samples, frame=1024, frame_step = 512
  // Calculate Hamming-window coefficients
  for(int i = 0; i < frame_size; i++){
    hamming_window[i] = 0.54 - 0.46 * hls::cos(2*PI*i/(frame_size-1));
  }
  for(int frame = 0; frame < (num_samples - frame_step); frame += frame_step)
  {
    // Fill the window array with windowed FFT samples
    for(int i = 0; i < frame_size; i++)
    {
      // Perform Hamming-windowing while copying sample. Voice-data is only real, so ignore the imaginary part
      data_frame[i] = input_data[i + frame].real() * hamming_window[i];
      // TODO: Find Signal-to-noise ratio
      to_FFT[i] = data_frame[i];
    }
    cout << "Done hamming windowing" << endl;
    FFT(to_FFT, from_FFT, 1, overflow);
    cout << "Done FFT" << endl;

    // Calculate the periodogram-based power spectral estimate of the first half of the signal
    for(int j = 0; j < frame_size/2; j++){
    	// Scale the output with 1024 after down-scaling during FFT
    	data_frame[j] = cmpxDataIn(from_FFT[j].real() << 11, from_FFT[j].imag() << 11);
    	output_data[j + frame] = (data_frame[j].real() * data_frame[j].real() + data_frame[j].imag() * data_frame[j].imag()) / frame_size;
    }
  }
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
    filterbanks[i] = hls::floor((FFT_size + 1) * filterbanks[i] / samplerate);
    // Create filterbank filters
    if((i > 1) && (i < (num_filterbanks + 2)))
    {
      generate_filterbank(filterbank_filters[i-2], filterbanks[i-2], filterbanks[i-1], filterbanks[i], FFT_size);
    }
  }
  delete[] filterbanks;

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
  int num_samples = num_frames * FFT_size / 2;
  // Allocate memory for the filterbanks
  double** filterbank_energies = new double*[num_frames];
  for(int frame = 0; frame < num_frames; frame++){
    filterbank_energies[frame] = new double[num_filterbanks];
    for(int filterbank = 0; filterbank < num_filterbanks; filterbank++)
      filterbank_energies[frame][filterbank] = 0;
  }

  // Allocate memory for DCT buffer. Re-use FFT for calculating DCT
  int num_DCT_energies = 4 * num_filterbanks;
  complex<double>* DCT_energies = new complex<double>[NUM_SAMPLES_PER_FFT];
  for(int i = 0; i < NUM_SAMPLES_PER_FFT; i++)
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
      }
    }
    // Create DCT input array
    int j = 0;
    for(int i = 0; i < num_DCT_energies; i++)
      {
        if(i < num_DCT_energies/2)
          {
            if((i % 2 != 0)){
              DCT_energies[i] = DCT_energies[num_DCT_energies - i] = hls::log(filterbank_energies[FFT_frame][j]);
              j++;
            }
          }
      }
    // Perform DCT for the current frame and copy the result back to filterbank_energies
    //FFT(DCT_energies, num_DCT_energies, 1);
    //for(int MFCC_value = 0; MFCC_value < num_filterbanks; MFCC_value++)
     // filterbank_energies[FFT_frame][MFCC_value] = DCT_energies[MFCC_value].real();
  }
  delete[] DCT_energies;
  return(filterbank_energies);
}

double freq_to_mel(double freq){
  return(1125 * hls::log(1 + freq/700));

}
double mel_to_freq(double mel){
  return(700 * (hls::exp(mel/1125) - 1));
}
