#include <hls_math.h>
#include <hls_fft.h>
#include <ap_fixed.h>

#define NUM_SAMPLES 16384
#define NUM_SAMPLES_PER_FFT 512
#define NUM_SAMPLES_PER_FFT_FRAME_STEP 256
#define NUM_SAMPLES_PER_FRAME NUM_SAMPLES_PER_FFT / 2
#define NUM_FRAMES ((NUM_SAMPLES/NUM_SAMPLES_PER_FFT_FRAME_STEP) - 1)
#define NUM_SAMPLES_POST_FRAMING NUM_FRAMES * NUM_SAMPLES_PER_FFT / 2

#define FFT_INPUT_WIDTH 32 //24 for max. 0.7% error
#define FFT_OUTPUT_WIDTH FFT_INPUT_WIDTH
#define FFT_LENGTH 512
#define DCT_LENGTH 	64

#define MEL_LOWEST_FREQUENCY 300
#define MEL_HIGHEST_FREQUENCY 8000
#define MEL_NUM_FILTERBANKS 16
#define NUM_MFCC_COEFFICIENTS MEL_NUM_FILTERBANKS/2 - 1

struct FFT_params : hls::ip_fft::params_t {
	static const unsigned ordering_opt = hls::ip_fft::natural_order;
	static const unsigned input_width = FFT_INPUT_WIDTH;
	static const unsigned output_width = FFT_OUTPUT_WIDTH;
	static const unsigned config_width = 24; //DEFAULT: 24 , Radix-2: 32
	static const bool has_nfft = 1;
	//static const unsigned arch_opt = 2; // DEFAULT: Stream, 2: Radix-2
    static const unsigned max_nfft = 9; // DEFAULT: 10
	//static const unsigned scaling_opt = 1;

};

typedef	ap_fixed<FFT_INPUT_WIDTH,1> data_in_t;
typedef ap_fixed<FFT_OUTPUT_WIDTH,FFT_OUTPUT_WIDTH-FFT_INPUT_WIDTH + 1> data_out_t;
typedef std::complex<data_in_t> cmpxDataIn;
typedef std::complex<data_out_t> cmpxDataOut;
typedef hls::ip_fft::config_t<FFT_params> config_t;
typedef hls::ip_fft::status_t<FFT_params> status_t;

using namespace std;

void MFCC_main(cmpxDataIn wav_data[NUM_SAMPLES], data_out_t energies[NUM_FRAMES][NUM_MFCC_COEFFICIENTS]);
