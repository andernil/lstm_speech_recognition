#include "hamming_original.h"
#include <iostream>

#define PI 3.1415926535

#define SAMPLING_FREQUENCY 48000

bool direction = 0;

using namespace std;
void read_FFT_data(status_t* status_in, bool* ovflo, cmpxDataOut out[FFT_LENGTH], cmpxDataOut from_FFT[FFT_LENGTH]);
void write_FFT_data(bool direction, config_t* fft_config, cmpxDataIn in[FFT_LENGTH], cmpxDataIn to_FFT[FFT_LENGTH], bool DCT);
void FFT(complex<data_in_t> in[FFT_LENGTH], complex<data_out_t> out[FFT_LENGTH], bool direction, bool* ovflo, bool DCT);
void window_FFT(cmpxDataIn input_data[NUM_SAMPLES], data_out_t output_data[NUM_SAMPLES_POST_FRAMING]);
void init_mel(double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME], double min_frequency, double max_frequency, int num_filterbanks, int FFT_size, int samplerate);
void generate_filterbank(double* filterbank, double prev_filterbank, double curr_filterbank, double next_filterbank, int FFT_size);
void calculate_filterbank_energies(data_out_t input_data[NUM_SAMPLES_POST_FRAMING], double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME], data_out_t MFCC_coefficients[NUM_FRAMES][NUM_MFCC_COEFFICIENTS], int num_filterbanks, int num_frames, int frame_size, int FFT_size);
double freq_to_mel(double freq);
double mel_to_freq(double mel);

void MFCC_main(cmpxDataIn wav_data[NUM_SAMPLES], data_out_t energies[NUM_FRAMES][NUM_MFCC_COEFFICIENTS], int sampling_frequency)
{
	double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME];
	data_out_t power_data[NUM_SAMPLES_POST_FRAMING];
  window_FFT(wav_data, power_data);
  init_mel(filters, MEL_LOWEST_FREQUENCY, MEL_HIGHEST_FREQUENCY, MEL_NUM_FILTERBANKS, NUM_SAMPLES_PER_FFT, SAMPLING_FREQUENCY);
  calculate_filterbank_energies(power_data, filters, energies, MEL_NUM_FILTERBANKS, NUM_FRAMES, NUM_SAMPLES_PER_FRAME, NUM_SAMPLES_PER_FFT);

}

void write_FFT_data(bool direction, config_t* fft_config, cmpxDataIn in[FFT_LENGTH], cmpxDataIn to_FFT[FFT_LENGTH], bool DCT)
{
	fft_config->setDir(direction);
	//fft_config->setSch(0x2AB); // For pipelined
	//fft_config->setSch(0x55556); //for Radix2
	if(DCT){
		fft_config->setNfft(6);
		fft_config->setSch(0x0);
	}
	else{
		fft_config->setNfft(10);
		fft_config->setSch(0x55556);
	}
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

void FFT(complex<data_in_t> in[FFT_LENGTH], complex<data_out_t> out[FFT_LENGTH], bool direction, bool* ovflo, bool DCT)
{
#pragma HLS interface ap_hs port=direction
#pragma HLS interface ap_fifo depth=1 port=ovflo
#pragma HLS interface ap_fifo depth=FFT_LENGTH port=in,out
#pragma HLS data_pack variable=in
#pragma HLS data_pack variable=out
#pragma HLS dataflow
	config_t FFT_config1;
	status_t FFT_status1;
	complex<data_in_t> x_in[FFT_LENGTH];
	complex<data_out_t> x_out[FFT_LENGTH];

	write_FFT_data(direction, &FFT_config1, in, x_in, DCT);
	hls::fft<FFT_params>(x_in, x_out, &FFT_status1, &FFT_config1);
	read_FFT_data(&FFT_status1, ovflo, out, x_out);
}

void window_FFT(cmpxDataIn input_data[NUM_SAMPLES], data_out_t output_data[NUM_SAMPLES_POST_FRAMING])
{
	int frame_size = NUM_SAMPLES_PER_FFT;
	int frame_step = NUM_SAMPLES_PER_FFT_FRAME_STEP;
	int num_samples = NUM_SAMPLES;
	bool overflow;
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
    FFT(to_FFT, from_FFT, 1, &overflow, 0);
    if(overflow)
    	cout << "Overflow during FFT " << frame/frame_size << endl;
    cout << "Done FFT" << endl;

    // Calculate the periodogram-based power spectral estimate of the first half of the signal
    for(int j = 0; j < frame_size/2; j++){
    	// Scale the output with 1024 after down-scaling during FFT
    	data_frame[j] = cmpxDataOut(from_FFT[j].real() << 11, from_FFT[j].imag() << 11);
    	output_data[j + frame] = ((data_frame[j].real() * data_frame[j].real()) + (data_frame[j].imag() * data_frame[j].imag())) / frame_size;
    }
  }
}

void init_mel(double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME], double min_frequency, double max_frequency, int num_filterbanks, int FFT_size, int samplerate){
  double min_mel = freq_to_mel(min_frequency);
  double max_mel = freq_to_mel(max_frequency);
  double filterbank_step = (max_mel - min_mel) / (num_filterbanks + 1);
  // The number of filterbanks is always n+2
  double filterbanks [num_filterbanks + 2];
  for(int i = 0; i < num_filterbanks + 2; i++){
    filterbanks[i] = min_mel + filterbank_step * i;
    // Convert back to frequency
    filterbanks[i] = mel_to_freq(filterbanks[i]);
    // Round frequencies to a precision we have
    filterbanks[i] = hls::floor((FFT_size + 1) * filterbanks[i] / samplerate);
    // Create filterbank filters
    if((i > 1) && (i < (num_filterbanks + 2)))
    {
      generate_filterbank(filters[i-2], filterbanks[i-2], filterbanks[i-1], filterbanks[i], FFT_size);
    }
  }
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
void calculate_filterbank_energies(data_out_t input_data[NUM_SAMPLES_POST_FRAMING],
	double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME], data_out_t MFCC_coefficients[NUM_FRAMES][NUM_MFCC_COEFFICIENTS], int num_filterbanks, int num_frames, int frame_size, int FFT_size)
{
  // Allocate memory for DCT buffer. Re-use FFT for calculating DCT
  int num_DCT_energies = 4 * num_filterbanks;
  cmpxDataIn DCT_energies [NUM_SAMPLES_PER_FFT];
  cmpxDataOut MFCC_energies[NUM_SAMPLES_PER_FFT];
  double output_energies[NUM_FRAMES][MEL_NUM_FILTERBANKS];
  bool overflow = false;
  double temp_power_data = 0;

  // Run filters over each frame. Frames are 512, as are the filters.
  for(int FFT_frame = 0; FFT_frame < num_frames; FFT_frame++)
  {
    // Calculate sum for each filterbank for each frame
    for(int filterbank = 0; filterbank < num_filterbanks; filterbank++)
    {
      for(int power_data = 0; power_data < frame_size; power_data++)
      {
    	temp_power_data = input_data[power_data + (FFT_frame * frame_size)];
        output_energies[FFT_frame][filterbank] += temp_power_data * filters[filterbank][power_data];
      }
    }

    // Create DCT input array
    for(int i = 0; i < NUM_SAMPLES_PER_FFT; i++){
    	DCT_energies[i] = 0;
    }
    int j = 0;
    for(int i = 0; i < num_DCT_energies; i++)
      {
        if(i < num_DCT_energies/2)
          {
            if((i % 2 != 0)){
              double temp_DCT_energy = hls::log(output_energies[FFT_frame][j]);
            	//double temp_DCT_energy = test_energies[j] * 1024;
              if(temp_DCT_energy == -1.0/0.0){
            	  temp_DCT_energy = -21;
              }
              DCT_energies[i] = DCT_energies[num_DCT_energies - i] = temp_DCT_energy / 1024;
              //cout << "Filterbank log "<< j << ": " << temp_DCT_energy << endl;
              //cout << DCT_energies[i].real() << ", ";
              j++;
            }
          }
        //if(FFT_frame == 0)
        	//cout << "DCT " << i << ": " << DCT_energies[i] << endl;
      }
    // Perform DCT for the current frame and copy the result back to filterbank_energies
    FFT(DCT_energies, MFCC_energies, 1, &overflow, 1);
    if(overflow)
	cout << "ERROR: Overflow during DCT" << endl;
	for(int i = 0; i < NUM_MFCC_COEFFICIENTS; i++){
		MFCC_coefficients[FFT_frame][i] = MFCC_energies[i + 1].real();
		//cout << "MFCC " << i << ": " << MFCC_coefficients[FFT_frame][i] << endl;
	}
  }
}

double freq_to_mel(double freq){
  return(1125 * hls::log(1 + freq/700));

}
double mel_to_freq(double mel){
  return(700 * (hls::exp(mel/1125) - 1));
}
