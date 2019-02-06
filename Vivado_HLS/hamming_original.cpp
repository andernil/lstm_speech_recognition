#include <iostream>
#include <complex>

#define PI 3.1415926535
#define NUM_SAMPLES 8

using namespace std;

void separate(complex<double>* input_data, int num_samples);
void FFT(complex<double>* input_data, int num_samples);

int main()
{
  complex<double> test_data[NUM_SAMPLES];
  for(int i = 0; i < NUM_SAMPLES; i++)
  {
    test_data[i] = i;
    cout << test_data[i] << endl;
  }
  FFT(test_data, NUM_SAMPLES);
  cout << "Result:" << endl;
  for(int i = 0; i < NUM_SAMPLES; i++)
    cout << test_data[i] << endl;
  return(0);
}


void separate (complex<double>* input_data, int num_samples)
{
  complex<double>* temp_buffer = new complex<double>[num_samples/2];
  //Copy all odd elements to temp buffer
  for(int i = 0; i < num_samples/2; i++)
    temp_buffer[i] = input_data[i*2+1];
  //Copy all even elements to lower half of input_data
  for(int i = 0; i < num_samples/2; i++)
    input_data[i] = input_data[i*2];
  //Copy all odd elements from buffer to upper half of input_data
  for(int i = 0; i < num_samples/2; i++)
    input_data[i+num_samples/2] = temp_buffer[i];
  //Delete the allocated temp buffer
  delete[] temp_buffer;
}

void FFT(complex<double>* input_data, int num_samples)
{
  if(num_samples < 2)
    asm("NOP");
  else
  {
    // Separate all even numbers to lower half, odd to upper half
    separate(input_data, num_samples);
    //Recurse even items
    FFT(input_data, num_samples/2);
    //Recurse odd times
    FFT(input_data + num_samples/2, num_samples/2);
    for(int i = 0; i < num_samples/2; i++)
    {
      complex<double> even = input_data[i];
      complex<double> odd = input_data[i+num_samples/2];
      complex<double> twiddle_factor = exp(complex<double>(0, -2 * PI * i/num_samples));
      input_data[i] = even + twiddle_factor * odd;
      input_data[i + num_samples/2] = even - twiddle_factor * odd;
    }
  }
}

