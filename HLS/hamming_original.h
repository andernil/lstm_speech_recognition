#include <hls_math.h>

#include "FFT_top.h"

#define NUM_SAMPLES 16000
#define NUM_SAMPLES_PER_FFT 1024
#define FRAME_STEP_LENGTH 128
#define NUM_SAMPLES_PER_FRAME NUM_SAMPLES_PER_FFT / 2
#define NUM_FRAMES (NUM_SAMPLES - NUM_SAMPLES_PER_FFT) / FRAME_STEP_LENGTH + 1

#define MEL_LOWEST_FREQUENCY 300
#define MEL_HIGHEST_FREQUENCY 8000
#define MEL_NUM_FILTERBANKS 80

const int NUM_SAMPLES_POST_FFT = int(NUM_FRAMES) * int(NUM_SAMPLES_PER_FRAME);
const int NUM_MEL_BANKS_TOTAL = int(NUM_FRAMES) * int(MEL_NUM_FILTERBANKS);

void dut_main(complex<double> wav_data[NUM_SAMPLES],
			  double energies[NUM_FRAMES][MEL_NUM_FILTERBANKS],
			  int peak_value);
