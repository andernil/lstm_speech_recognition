/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
#include <stdio.h>
#include "platform.h"

#if 0 // The original 'Hello World' code
void print(char *str);

int main()
{
    init_platform();

    print("Hello World\n\r");

    return 0;
}
#else

#include <stdlib.h> // Std C functions, e.g. exit()
#include <math.h>   // libm header: sqrt(), cos(), etc
#include "xparameters.h" // System parameter definitions
#include "xaxidma.h" // Device driver API for AXI DMA
#include "xtime_l.h" // For time

#include "input_wav.h"
// Define the length of the (real input) FFT data
#define NUM_SAMPLES 16000
#define REAL_FFT_LEN  1024
#define FRAME_STEP_LENGTH 128
#define NUM_FRAMES (NUM_SAMPLES - REAL_FFT_LEN) / FRAME_STEP_LENGTH + 1
#define NUM_SAMPLES_PER_FRAME REAL_FFT_LEN / 2


// Define a type to hold complex FFT output (real) spectral data
typedef struct {
   short re;
   short im;
} complex16;

// Helper function forward declarations
int init_dma(XAxiDma *axiDma);
void generate_waveform(short *signal_buf, int num_samples);
float load_data(short *signal_buf, int num_samples);

// Program entry point
int main()
{
	// Declare a XAxiDma object instance
   XAxiDma axiDma;

   // Local variables
   int i, j;
   int status;
   float peak_value = 0;
   //static short realdata[4*REAL_FFT_LEN];
   static short realdata[NUM_SAMPLES];
   static short to_FFT[REAL_FFT_LEN];
   volatile static complex16 realspectrum[REAL_FFT_LEN/2];

   // Time variables
   XTime tStart, tStop;

   // Initialize the platform
   init_platform();
   print("---------------------------------------\n\r");
   print("- RealFFT PL accelerator test program -\n\r");
   print("---------------------------------------\n\r");

   // Initialize the (simple) DMA engine
   status = init_dma(&axiDma);
   if (status != XST_SUCCESS) {
      exit(-1);
   }
   // Generate a waveform to be input to FFT
   //for (i = 0; i < 4; i++)
   print("Loading input_data");
   //generate_waveform(realdata, REAL_FFT_LEN);
   peak_value = load_data(realdata, NUM_SAMPLES);
   //generate_waveform(to_FFT, REAL_FFT_LEN);
   // *IMPORTANT* - flush contents of 'realdata' from data cache to memory
   // before DMA. Otherwise DMA is likely to get stale or uninitialized data
   //Xil_DCacheFlushRange((unsigned)realdata, 4 * REAL_FFT_LEN * sizeof(short));
   print("Flushing data to cache");
   Xil_DCacheFlushRange((unsigned)realdata, NUM_SAMPLES * sizeof(short));
   // DMA enough data to push out first result data set completely
   print("Transferring some data");

   // Prepare preload data
   static short predata [REAL_FFT_LEN * 4];
   for(int i = 0; i < 4; i++)
   {
	   for(int j = 0; j < REAL_FFT_LEN; j++)
		   predata[j + (i * REAL_FFT_LEN)] = realdata[j + (i * FRAME_STEP_LENGTH)];
   }
   // Fill the buffer with the first data
   status = XAxiDma_SimpleTransfer(&axiDma, (u32)predata,
		   4 * REAL_FFT_LEN * sizeof(short), XAXIDMA_DMA_TO_DEVICE);

   /*
   status = XAxiDma_SimpleTransfer(&axiDma, (u32)realdata,
		   4 * REAL_FFT_LEN * sizeof(short), XAXIDMA_DMA_TO_DEVICE);
   */

   // Do multiple DMA xfers from the RealFFT core's output stream and
   // display data for bins with significant energy. After the first frame,
   // there should only be energy in bins around the frequencies specified
   // in the generate_waveform() function - currently bins 191~193 only

   XTime_GetTime(&tStart);
   for (i = 0; i < NUM_FRAMES; i++) {
	   for(int j = 0; j < REAL_FFT_LEN; j++)
		   to_FFT[j] = realdata[j + (i * FRAME_STEP_LENGTH)];
	   // Setup DMA from PL to PS memory using AXI DMA's 'simple' transfer mode
	   status = XAxiDma_SimpleTransfer(&axiDma, (u32)realspectrum,
			   REAL_FFT_LEN / 2 * sizeof(complex16), XAXIDMA_DEVICE_TO_DMA);
      // Poll the AXI DMA core
	   do {
		   status = XAxiDma_Busy(&axiDma, XAXIDMA_DEVICE_TO_DMA);
	   } while(status);
	   // Data cache must be invalidated for 'realspectrum' buffer after DMA
	   Xil_DCacheInvalidateRange((unsigned)realspectrum,
	   		REAL_FFT_LEN / 2 * sizeof(complex16));
	   // DMA another frame of data to PL
	   if (!XAxiDma_Busy(&axiDma, XAXIDMA_DMA_TO_DEVICE))
		   status = XAxiDma_SimpleTransfer(&axiDma, (u32)to_FFT,
				   REAL_FFT_LEN * sizeof(short), XAXIDMA_DMA_TO_DEVICE);

	   //printf("\n\rFrame %d received:\n\r", i);
	   // Detect energy in spectral data above a set threshold
	   /*
	   for (j = 0; j < REAL_FFT_LEN / 2; j++) {
		   /*
	   	// Convert the fixed point (s.15) values into floating point values
		   float real = (float)realspectrum[j].re / 32767.0f;
		   float imag = (float)realspectrum[j].im / 32767.0f;
		   float mag = sqrtf(real * real + imag * imag);
		   if (mag > 0.00390625f) {
			   printf("Energy detected in bin %3d - ",j);
			   printf("{%8.5f, %8.5f}; mag = %8.5f\n\r", real, imag, mag);
		   }

		   float real = (float)realspectrum[j].re / peak_value;// / peak_value;
		   //signed short real_int = realspectrum[j].re;
		   float imag = (float)realspectrum[j].im / peak_value;// / peak_value;
		   //signed short imag_int = realspectrum[j].im;
		   float mag = (real * real + imag * imag);
		   //signed short mag = (real_int * real_int + imag_int * imag_int);

		   //printf("re: %d, img: %d...", real_int, imag_int);
		   //printf("%f,", mag);



	   //printf("End of frame.\n\r");
	   if(i % 10 == 0)
		   printf("\n");
	   fflush(stdout);
	   */
   }
   XTime_GetTime(&tStop);

   printf("Num clock cycles: %llu \n", 2*(tStop-tStart));
   printf("Time spent: %.2f us \n", 1.0 * (tStop - tStart) / (COUNTS_PER_SECOND/1000000));
   printf("***************\n\r");
   printf("* End of test *\n\r");
   printf("***************\n\r\n\r");
   return 0;
}

// A function that generates a waveform with a period of 'num_samples'
void generate_waveform(short *signal_buf, int num_samples)
{
   const float cycles_per_win = 192.0f;
   const float phase = 0.0f;
   const float ampl = 0.9f;
   int i;
   for (i = 0; i < num_samples; i++) {
      float sample = ampl *
         cosf((i * 2 * M_PI * cycles_per_win / (float)num_samples) + phase);
      //printf("%f", sample);
      signal_buf[i] = (short)(32767.0f * sample);
   }
}

// A function that wraps all AXI DMA initialization related API calls
int init_dma(XAxiDma *axiDmaPtr){
   XAxiDma_Config *CfgPtr;
   int status;
   // Get pointer to DMA configuration
   CfgPtr = XAxiDma_LookupConfig(XPAR_AXIDMA_0_DEVICE_ID);
   if(!CfgPtr){
      print("Error looking for AXI DMA config\n\r");
      return XST_FAILURE;
   }
   // Initialize the DMA handle
   status = XAxiDma_CfgInitialize(axiDmaPtr,CfgPtr);
   if(status != XST_SUCCESS){
      print("Error initializing DMA\n\r");
      return XST_FAILURE;
   }
   //check for scatter gather mode - this example must have simple mode only
   if(XAxiDma_HasSg(axiDmaPtr)){
      print("Error DMA configured in SG mode\n\r");
      return XST_FAILURE;
   }
   //disable the interrupts
   XAxiDma_IntrDisable(axiDmaPtr, XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DEVICE_TO_DMA);
   XAxiDma_IntrDisable(axiDmaPtr, XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DMA_TO_DEVICE);

   return XST_SUCCESS;
}
// Function for loading samples from input_wav.h and scaling them to +/-1
float load_data(short *signal_buf, int num_samples)
{
	signed short peak_value = 0;
	float temp_val = 0.0f;
	float peak_value_f = 0.0f;
	float scaling = 0.0f;
	signed short temp_abs = 0;
	short temp_out = 0;
	for(int i = 0; i < num_samples; i++)
	{
		temp_abs = abs(input_data[i]);
		if(temp_abs > peak_value)
			peak_value = temp_abs;
	}
	peak_value_f = peak_value;
	scaling = 32767.0f/peak_value_f;

	for(int i = 0; i < num_samples; i++)
	{
		temp_val = (float) input_data[i];
		temp_val *= scaling;
		temp_out = (short) temp_val;
		//temp_val /= peak_value_f;
		//signal_buf[i] = (short) temp_val;
		signal_buf[i] = temp_out;
	}
	return(scaling);
}

#endif
