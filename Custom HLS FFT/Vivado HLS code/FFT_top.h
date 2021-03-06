#include <complex>
#include <ap_fixed.h>
#include <hls_fft.h>

using namespace std;

#define FFT_LENGTH 1024

#define FFT_INPUT_WIDTH 32
#define FFT_OUTPUT_WIDTH FFT_INPUT_WIDTH

struct FFT_params : hls::ip_fft::params_t {
	static const unsigned ordering_opt = hls::ip_fft::natural_order;
	static const unsigned input_width = FFT_INPUT_WIDTH;
	static const unsigned output_width = FFT_OUTPUT_WIDTH;
	static const unsigned config_width = 24;
	static const unsigned arch_opt = 2;
    static const unsigned max_nfft = 10;
};

typedef	ap_fixed<FFT_INPUT_WIDTH,1> data_in_t;
typedef ap_fixed<FFT_OUTPUT_WIDTH,FFT_OUTPUT_WIDTH-FFT_INPUT_WIDTH + 1> data_out_t;
typedef std::complex<data_in_t> cmpxDataIn;
typedef std::complex<data_out_t> cmpxDataOut;

typedef hls::ip_fft::config_t<FFT_params> config_t;
typedef hls::ip_fft::status_t<FFT_params> status_t;

void write_FFT_data(
		config_t* fft_config,
		cmpxDataIn in[FFT_LENGTH],
		cmpxDataIn to_FFT[FFT_LENGTH]);

void read_FFT_data(status_t* status_in,
		bool* ovflo,
		cmpxDataOut out[FFT_LENGTH],
		cmpxDataOut from_FFT[FFT_LENGTH]);

void FFT(complex<data_in_t> in[FFT_LENGTH],
		 complex<data_out_t> out[FFT_LENGTH],
		 bool* ovflo);
