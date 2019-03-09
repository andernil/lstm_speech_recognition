#include "FFT_top.h"

using namespace std;

void write_FFT_data(
		bool direction,
		unsigned nFFT,
		unsigned scaling,
		config_t* fft_config,
		cmpxDataIn in[FFT_LENGTH],
		cmpxDataIn to_FFT[FFT_LENGTH])
{
	fft_config->setNfft(nFFT);
	//fft_config->setSch(0x15556);
	//fft_config->setSch(0x1AB);
	fft_config->setSch(scaling);

	fft_config->setDir(direction);
	int i;
	for(i = 0; i < FFT_LENGTH; i++)
		to_FFT[i] = in[i];
}

void read_FFT_data(status_t* status_in,
		bool* ovflo,
		cmpxDataOut out[FFT_LENGTH],
		cmpxDataOut from_FFT[FFT_LENGTH])
{
	int i;
	for(i = 0; i < FFT_LENGTH; i++){
		out[i] = from_FFT[i];
	}
	*ovflo = status_in->getOvflo() & 0x1;
}

void FFT(complex<data_in_t> in[FFT_LENGTH],
		complex<data_out_t> out[FFT_LENGTH],
		bool direction,
		bool* ovflo,
		unsigned nFFT,
		unsigned scaling)
{
#pragma HLS interface ap_hs port=direction
#pragma HLS interface ap_hs port=nFFT
#pragma HLS interface ap_hs port=scaling
#pragma HLS interface ap_fifo depth=1 port=ovflo
#pragma HLS interface ap_fifo depth=512 port=in,out
#pragma HLS data_pack variable=in
#pragma HLS data_pack variable=out
#pragma HLS dataflow
	complex<data_in_t> x_in[FFT_LENGTH];
	complex<data_out_t> x_out[FFT_LENGTH];
	config_t FFT_config;
	status_t FFT_status;

	write_FFT_data(direction, nFFT, scaling, &FFT_config, in, x_in);
	hls::fft<FFT_params>(x_in, x_out, &FFT_status, &FFT_config);
	read_FFT_data(&FFT_status, ovflo, out, x_out);
}
