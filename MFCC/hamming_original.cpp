#include "hamming_original.h"
#include <iostream>

#define PI 3.1415926535

#define SAMPLING_FREQUENCY 16000

using namespace std;

/*
void read_DCT_data(DCT_status_t* status_in, cmpxDataOut out[DCT_LENGTH], cmpxDataOut from_FFT[DCT_LENGTH]);
void write_DCT_data(bool direction, DCT_config_t* fft_config, cmpxDataIn in[DCT_LENGTH], cmpxDataIn to_FFT[DCT_LENGTH]);
void DCT(complex<data_in_t> in[DCT_LENGTH], complex<data_out_t> out[DCT_LENGTH], bool direction);
*/

void window_FFT(cmpxDataIn input_data[NUM_SAMPLES], double output_data[NUM_SAMPLES_POST_FRAMING]);
void init_mel(double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME], double min_frequency, double max_frequency, int num_filterbanks, int FFT_size, int samplerate);
void generate_filterbank(double* filterbank, double prev_filterbank, double curr_filterbank, double next_filterbank, int FFT_size);
void calculate_filterbank_energies(double input_data[NUM_SAMPLES_POST_FRAMING], double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME], data_out_t MFCC_coefficients[NUM_FRAMES][NUM_MFCC_COEFFICIENTS], int num_filterbanks, int num_frames, int frame_size, int FFT_size);

double freq_to_mel(double freq);
double mel_to_freq(double mel);

//static complex<data_in_t> to_FFT [NUM_SAMPLES_PER_FFT];
//static complex<data_out_t> from_FFT [NUM_SAMPLES_PER_FFT];

void MFCC_main(cmpxDataIn wav_data[NUM_SAMPLES], data_out_t energies[NUM_FRAMES][NUM_MFCC_COEFFICIENTS])
{
	double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME];
	double power_data[NUM_SAMPLES_POST_FRAMING];
	cout << "Performing window FFT" << endl;
  window_FFT(wav_data, power_data);
	cout << "Calculating mel-filterbanks" << endl;
  init_mel(filters, MEL_LOWEST_FREQUENCY, MEL_HIGHEST_FREQUENCY, MEL_NUM_FILTERBANKS, NUM_SAMPLES_PER_FFT, SAMPLING_FREQUENCY);
  cout << "Performing MFCC calculations with DCT" << endl;
  calculate_filterbank_energies(power_data, filters, energies, MEL_NUM_FILTERBANKS, NUM_FRAMES, NUM_SAMPLES_PER_FRAME, NUM_SAMPLES_PER_FFT);
  cout << "Done calculating MFCC values" << endl;
}
/*
void write_DCT_data(bool direction, DCT_config_t* fft_config, cmpxDataIn in[DCT_LENGTH], cmpxDataIn to_DCT[DCT_LENGTH])
{
	fft_config->setDir(direction);
	//fft_config->setSch(0x15556);
	fft_config->setSch(0x0);

	int i;
	for(i = 0; i < DCT_LENGTH; i++)
		to_DCT[i] = in[i];
}
void read_DCT_data(DCT_status_t* status_in, cmpxDataOut out[DCT_LENGTH], cmpxDataOut from_DCT[DCT_LENGTH])
{
	int i;
	for(i = 0; i < DCT_LENGTH; i++){
		out[i] = from_DCT[i];
	}
	*ovflo = status_in->getOvflo() & 0x1;
}

void DCT(complex<data_in_t> in[DCT_LENGTH], complex<data_out_t> out[DCT_LENGTH], bool direction)
{
#pragma HLS interface ap_hs port=direction
//#pragma HLS interface ap_fifo depth=1 port=ovflo
#pragma HLS interface ap_fifo depth=64 port=in,out
#pragma HLS data_pack variable=in
#pragma HLS data_pack variable=out
#pragma HLS dataflow
	complex<data_in_t> x_in[DCT_LENGTH];
	complex<data_out_t> x_out[DCT_LENGTH];
	DCT_config_t DCT_config;
	DCT_status_t DCT_status;

	write_DCT_data(direction, &DCT_config, in, x_in);
//	hls::fft<DCT_params>(x_in, x_out, &DCT_status, &DCT_config);
	read_DCT_data(&DCT_status, out, x_out);
}
*/

void window_FFT(cmpxDataIn input_data[NUM_SAMPLES], double output_data[NUM_SAMPLES_POST_FRAMING])
{
	static complex<data_in_t> to_FFT [NUM_SAMPLES_PER_FFT];
	static complex<data_out_t> from_FFT [NUM_SAMPLES_PER_FFT];
	int frame_size = NUM_SAMPLES_PER_FFT;
	int frame_step = NUM_SAMPLES_PER_FFT_FRAME_STEP;
	int num_samples = NUM_SAMPLES;
	bool overflow = false;
  cmpxDataIn data_frame [NUM_SAMPLES_PER_FFT];
  data_in_t hamming_window [NUM_SAMPLES_PER_FFT];

  //cout << "Declared variables" << endl;
  // Slide the frame along the array of samples, frame=512, frame_step = 256
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
      //if(frame == 0)
    //	  cout << data_frame[i] << ", ";
      to_FFT[i] = data_frame[i];
    }
    //cout << "Done hamming windowing" << endl;
    FFT(to_FFT, from_FFT, 1, &overflow, 9, 0x1AB);
    //if(overflow)
    	//cout << "ERROR: Overflow during FFT " << frame/frame_size << endl;
    //cout << "Done FFT" << endl;

    // Calculate the periodogram-based power spectral estimate of the first half of the signal
    for(int j = 0; j < NUM_SAMPLES_PER_FFT/2; j++){
    	// Scale the output with 10 bits after down-scaling during FFT
    	data_frame[j] = cmpxDataOut(from_FFT[j].real() << 10, from_FFT[j].imag() << 10);
    	output_data[j + frame] =  ((data_frame[j].real() * data_frame[j].real()) + (data_frame[j].imag() * data_frame[j].imag())) / frame_size;
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

void calculate_filterbank_energies(double input_data[NUM_SAMPLES_POST_FRAMING],
	double filters[MEL_NUM_FILTERBANKS][NUM_SAMPLES_PER_FRAME],
	data_out_t MFCC_coefficients[NUM_FRAMES][NUM_MFCC_COEFFICIENTS],
	int num_filterbanks, int num_frames, int frame_size, int FFT_size)
{
  // Allocate memory for DCT buffer. Re-use FFT for calculating DCT
  int num_DCT_energies = 4 * num_filterbanks;
  static cmpxDataIn DCT_energies [FFT_LENGTH];
  static cmpxDataOut MFCC_energies[FFT_LENGTH];
  double output_energies[NUM_FRAMES][MEL_NUM_FILTERBANKS];
  bool overflow = false;
  double temp_power_data = 0;
  double temp_DCT_energy = 0;

  // Run filters over each frame. Frames are 512, as are the filters.
  for(int FFT_frame = 0; FFT_frame < num_frames; FFT_frame++)
  {
    // Calculate sum for each filterbank for each frame
    for(int filterbank = 0; filterbank < num_filterbanks; filterbank++)
    {
      output_energies[FFT_frame][filterbank] = 0;
      for(int power_data = 0; power_data < frame_size; power_data++)
      {
        output_energies[FFT_frame][filterbank] += input_data[power_data + (FFT_frame * frame_size)] * filters[filterbank][power_data];
        //if(FFT_frame == 58)
        //	cout << "Filterbank: " << filterbank << ": " << output_energies[52][filterbank] << endl;
      }
      cout << "[" << FFT_frame << ", " << filterbank << "]" << output_energies[FFT_frame][filterbank] << endl;
     // if(FFT_frame == 58)
    	//  cout << "Filterbank: " << filterbank << ": " << output_energies[58][filterbank] << endl;
    }

    // Create DCT input array
    for(int i = 0; i < FFT_LENGTH; i++){
    	DCT_energies[i] = 0;
    	MFCC_energies[i] = 0;
    }
    int j = 0;
    for(int i = 0; i < num_DCT_energies; i++)
      {
        if(i < num_DCT_energies/2)
          {
            if((i % 2 != 0)){
              temp_DCT_energy = hls::log(output_energies[FFT_frame][j]);
            	//double temp_DCT_energy = test_energies[j] * 1024;
              if(temp_DCT_energy == -1.0/0.0){
            	  temp_DCT_energy = -21;
            	  //cout << "Threshold reached" << endl;
              }
              DCT_energies[i] = DCT_energies[num_DCT_energies - i] = temp_DCT_energy / (1024);
              //if(FFT_frame == 58){
                //cout << "Energy " << j << " pre-scaling: " << output_energies[FFT_frame][j] << endl;
                //cout << "Filterbank energy log" << j << ": " << (hls::log(output_energies[FFT_frame][j])) << endl;
                //cout << "Filterbank log energy " << j << ": " << DCT_energies[i] << endl;
              //}

              j++;
            }
          }
      }
    cout << "Performing DCT: " << FFT_frame  << endl;
    // Perform DCT for the current frame and copy the result back to filterbank_energies
    FFT(DCT_energies, MFCC_energies, 1, &overflow, 6, 0x0);
    //if(overflow)
    	//cout << "ERROR: Overflow during DCT" << endl;
	for(int i = 0; i < MEL_NUM_FILTERBANKS; i++){
		if(i > 0 && i < 8)
			MFCC_coefficients[FFT_frame][i - 1] = MFCC_energies[i].real();
		//if(FFT_frame == 58)
			//cout << "MFCC " << i << ": " << (MFCC_energies[i]) << endl;
	}
  }
}

double freq_to_mel(double freq){
  return(1125 * hls::log(1 + freq/700));

}
double mel_to_freq(double mel){
  return(700 * (hls::exp(mel/1125) - 1));
}
