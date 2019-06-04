#include "hamming_original.h"

#define PI 3.1415926535

#define SAMPLING_FREQUENCY 16000

using namespace std;

void window_FFT(complex<double> input_data[NUM_SAMPLES],
				double output_data[NUM_SAMPLES_POST_FFT],
				int peak_value);

void init_mel(double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME],
			  double min_frequency,
			  double max_frequency,
			  int num_filterbanks,
			  int FFT_size,
			  int samplerate);

void generate_filterbank(double* filterbank,
						 double prev_filterbank,
						 double curr_filterbank,
						 double next_filterbank,
						 int FFT_size);

void calculate_filterbank_energies(double input_data[NUM_SAMPLES_POST_FFT],
								   double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME],
								   double filterbank_energies[NUM_FRAMES][MEL_NUM_FILTERBANKS]);

double freq_to_mel(double freq);
double mel_to_freq(double mel);

void dut_main(complex<double> wav_data[NUM_SAMPLES],
			  double energies[NUM_FRAMES][MEL_NUM_FILTERBANKS],
			  int peak_value)
{
  double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME];
  static double power_data[NUM_SAMPLES_POST_FFT];
  static complex<double> input_wav[NUM_SAMPLES];
  for(int i = 0; i < NUM_SAMPLES; i++)
	input_wav[i] = wav_data[i].real();
  window_FFT(input_wav, power_data, peak_value);
  init_mel(filters, MEL_LOWEST_FREQUENCY, MEL_HIGHEST_FREQUENCY,
		   MEL_NUM_FILTERBANKS, NUM_SAMPLES_PER_FFT, SAMPLING_FREQUENCY);
  calculate_filterbank_energies(power_data, filters, energies);
}

void window_FFT(complex<double> input_data[NUM_SAMPLES],
			    double output_data[NUM_SAMPLES_POST_FFT],
			    int peak_value)
{
  int frame_size = NUM_SAMPLES_PER_FFT;
  int frame_step = FRAME_STEP_LENGTH;
  bool overflow = false;
  cmpxDataOut temp_output_frame[NUM_SAMPLES_PER_FRAME];
  double data_frame [NUM_SAMPLES_PER_FFT];
  double hamming_window [NUM_SAMPLES_PER_FFT];
  double scaling = peak_value * (1 << 9);
  static complex<data_in_t> to_FFT [NUM_SAMPLES_PER_FFT];
  static complex<data_out_t> from_FFT [NUM_SAMPLES_PER_FFT];

//	Comment these pragmas out if synthesising with FFT as the top function
#pragma HLS stream variable=to_FFT depth=1024
#pragma HLS data_pack variable=to_FFT
#pragma HLS stream variable=from_FFT depth=1024
#pragma HLS data_pack variable=from_FFT

  // Calculate Hamming-window coefficients
  for(int i = 0; i < frame_size; i++){
    hamming_window[i] = (0.54 - 0.46 * hls::cos(2*PI*i/(frame_size-1))) / scaling;
  }
  // Scale values and calculate the FFT using the sliding window technique
  for(int frame = 0; frame < NUM_FRAMES; frame++)
  {
    for(int i = 0; i < frame_size; i++)
    {
      data_frame[i] = 0;
      data_frame[i] = input_data[i + (frame * frame_step)].real() * hamming_window[i];
    }
    // Perform another copy loop to solve any conversion issues between double and ap_fixed
    for(int i = 0; i < frame_size; i++)
    {
      to_FFT[i] = data_frame[i];
    }
    // Perform FFT using FFT IP Core
    FFT(to_FFT, from_FFT, &overflow);

    // Calculate the periodogram-based power spectral estimate of the first half of the signal
    for(int j = 0; j < NUM_SAMPLES_PER_FRAME; j++){
    	// Scale the output with 10 bits after down-scaling during FFT
    	temp_output_frame[j] = cmpxDataOut(from_FFT[NUM_SAMPLES_PER_FFT - j].real() << 10,
    									   from_FFT[NUM_SAMPLES_PER_FFT - j].imag() << 10);
    	output_data[j + (frame * NUM_SAMPLES_PER_FRAME)] = ((temp_output_frame[j].real() * temp_output_frame[j].real())
    												      + (temp_output_frame[j].imag() * temp_output_frame[j].imag())) / frame_size;
    }
  }
}

void init_mel(double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME],
			  double min_frequency,
			  double max_frequency,
			  int num_filterbanks,
			  int FFT_size,
			  int samplerate)
{
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

void generate_filterbank(double* filterbank,
						 double prev_filterbank,
						 double curr_filterbank,
						 double next_filterbank,
						 int FFT_size)
{
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

void calculate_filterbank_energies(double input_data[NUM_SAMPLES_POST_FFT],
								   double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME],
								   double filterbank_energies[NUM_FRAMES][MEL_NUM_FILTERBANKS])
{
  double filter_avgs = 0;
  double num_filter_values = double(NUM_FRAMES) * double(MEL_NUM_FILTERBANKS);
  // Run filters over each frame. Frames are 512, as are the filters.
  for(int FFT_frame = 0; FFT_frame < NUM_FRAMES; FFT_frame++)
  {
    // Calculate sum for each filterbank for each frame
    for(int filterbank = 0; filterbank < MEL_NUM_FILTERBANKS; filterbank++)
    {
      filterbank_energies[FFT_frame][filterbank] = 0;
      for(int power_data = 0; power_data < NUM_SAMPLES_PER_FRAME; power_data++)
      {
        filterbank_energies[FFT_frame][filterbank] += input_data[power_data + (FFT_frame * NUM_SAMPLES_PER_FRAME)] * filters[filterbank][power_data];
      }
    }
  }

  for(int i = 0; i < NUM_FRAMES; i++){
    for(int j = 0; j < MEL_NUM_FILTERBANKS; j++){
      filterbank_energies[i][j] = 20 * hls::log10(filterbank_energies[i][j]);
      filter_avgs += filterbank_energies[i][j]/(num_filter_values);
    }
  }
  for(int i = 0; i < NUM_FRAMES; i++){
    for(int j = 0; j < MEL_NUM_FILTERBANKS; j++){
	  filterbank_energies[i][j] -= filter_avgs;
      }
    }
}
double freq_to_mel(double freq)
{
  return(1125 * hls::log(1 + freq/700));
}
double mel_to_freq(double mel)
{
  return(700 * (hls::exp(mel/1125) - 1));
}
