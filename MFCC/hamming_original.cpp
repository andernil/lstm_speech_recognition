#include "hamming_original.h"
//#include <iostream>

#define PI 3.1415926535

#define SAMPLING_FREQUENCY 16000

using namespace std;

void window_FFT(complex<double> input_data[NUM_SAMPLES], double output_data[NUM_SAMPLES_POST_FFT], int peak_value);
void init_mel(double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME], double min_frequency, double max_frequency, int num_filterbanks, int FFT_size, int samplerate);
void generate_filterbank(double* filterbank, double prev_filterbank, double curr_filterbank, double next_filterbank, int FFT_size);
void calculate_filterbank_energies(double input_data[NUM_SAMPLES_POST_FFT], double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME], double filterbank_energies[NUM_FRAMES][MEL_NUM_FILTERBANKS]);
double freq_to_mel(double freq);
double mel_to_freq(double mel);

void MFCC_main(complex<double> wav_data[NUM_SAMPLES], double energies[NUM_FRAMES][MEL_NUM_FILTERBANKS], int peak_value)
{
	double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME];
	static double power_data[NUM_SAMPLES_POST_FFT];
	static complex<double> input_wav[NUM_SAMPLES];
	for(int i = 0; i < NUM_SAMPLES; i++)
		input_wav[i] = wav_data[i].real();
	//cout << "Performing window FFT" << endl;
	//cout << "Peak value in: " << peak_value << endl;
  window_FFT(input_wav, power_data, peak_value);
	//cout << "Calculating mel-filterbanks" << endl;
  init_mel(filters, MEL_LOWEST_FREQUENCY, MEL_HIGHEST_FREQUENCY, MEL_NUM_FILTERBANKS, NUM_SAMPLES_PER_FFT, SAMPLING_FREQUENCY);
  //cout << "Performing MFCC calculations with DCT" << endl;
  calculate_filterbank_energies(power_data, filters, energies);
  //cout << "Done calculating mel values" << endl;
}

void window_FFT(complex<double> input_data[NUM_SAMPLES], double output_data[NUM_SAMPLES_POST_FFT], int peak_value)
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

#pragma HLS stream variable=to_FFT depth=1024
#pragma HLS data_pack variable=to_FFT
#pragma HLS stream variable=from_FFT depth=1024
#pragma HLS data_pack variable=from_FFT

  //cout << "Declared variables" << endl;
  // Slide the frame along the array of samples, frame=512, frame_step = 256
  // Calculate Hamming-window coefficients
  for(int i = 0; i < frame_size; i++){
    hamming_window[i] = (0.54 - 0.46 * hls::cos(2*PI*i/(frame_size-1))) / scaling;
  }

  for(int frame = 0; frame < NUM_FRAMES; frame++)
  {
    // Fill the window array with windowed FFT samples
    for(int i = 0; i < frame_size; i++)
    {
      data_frame[i] = 0;
      // Perform Hamming-windowing while copying sample. Voice-data is only real, so ignore the imaginary part
      data_frame[i] = input_data[i + (frame * frame_step)].real() * hamming_window[i];
      to_FFT[i] = data_frame[i];
    }
    //cout << "Done hamming windowing" << endl;
    FFT(to_FFT, from_FFT, &overflow);
    //if(overflow)
    	//cout << "ERROR: Overflow during FFT " << frame/frame_size << endl;
    //cout << "Done FFT" << endl;

    // Calculate the periodogram-based power spectral estimate of the first half of the signal
    for(int j = 0; j < NUM_SAMPLES_PER_FRAME; j++){
    	// Scale the output with 10 bits after down-scaling during FFT
    	temp_output_frame[j] = cmpxDataOut(from_FFT[j].real() << 10, from_FFT[j].imag() << 10);
    	output_data[j + (frame * NUM_SAMPLES_PER_FRAME)] = ((temp_output_frame[j].real() * temp_output_frame[j].real()) + (temp_output_frame[j].imag() * temp_output_frame[j].imag())) / frame_size;
    	//if(frame == 58 * NUM_SAMPLES_PER_FRAME){
    		//cout << "Pre hamming: " << input_data[j + frame] << endl;
    		//cout << "To FFT: " << to_FFT[j] << " and " << to_FFT[j + frame_step] << endl;
    		//cout << "From FFT: " << data_frame[j] << endl;
    		//cout << j << ": " << "Abs: " << output_data[j + frame] << endl;
    	//}
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

void calculate_filterbank_energies(
		double input_data[NUM_SAMPLES_POST_FFT],
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
        //if(FFT_frame == 58)
        //	cout << "Filterbank: " << filterbank << ": " << output_energies[52][filterbank] << endl;
      }
      //cout << "[" << FFT_frame << ", " << filterbank << "]" << output_energies[FFT_frame][filterbank] << endl;
     // if(FFT_frame == 58)
    	//  cout << "Filterbank: " << filterbank << ": " << output_energies[58][filterbank] << endl;
    }
  }

  for(int i = 0; i < NUM_FRAMES; i++){
    for(int j = 0; j < MEL_NUM_FILTERBANKS; j++){
  //    if(i == 0)
  //  	  cout << filterbank_energies[0][j] << endl;
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
double freq_to_mel(double freq){
  return(1125 * hls::log(1 + freq/700));

}
double mel_to_freq(double mel){
  return(700 * (hls::exp(mel/1125) - 1));
}
