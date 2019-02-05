#include <iostream>
#include <math.h>

using namespace std;

double pi = 4*atan((double)1);

void SWAP(float* data1, float* data2){
  float temp = *data1;
  *data1 = *data2;
  *data2 = temp;
}

int main(){
  return(0);
}

//data -> float array that represents the array of complex samples
//num_complex_samples -> number of samples (N^2 order number)
//isign -> 1 to calculate FFT and -1 to calculate Reverse FFT
float* FFT (float data[], unsigned long num_complex_samples, int isign){
  unsigned long n, mmax, m, j, istep, i;
  double wtemp, wr, wpr, wpi, wi, theta, tempr, tempi;

  //The complex array is real+complex so the array as a size
  //n = 2*number of complex samples. Real part is data[index] and
  //complex is data[index+1]
  n = num_complex_samples * 2;
  //binary inversion
  j = 1;
  for(i = 1; i < n;i+=2){
    //swap the real part
    SWAP(&data[j], &data[i]);
    //swap the complex part
    SWAP(&data[j+1], &data[i+1]);
    if((j/2)<(n/4)){
      //swap the real part
      SWAP(&data[(n-(i+2))], &data[(n-(j+2))]);
      //swap the complex part
      SWAP(&data[(n-(i+2))+1], &data[(n-(j+2))+1]);
    }
  }
  m = n/2;
  while (m >= 2 && j > m){
    j -= m;
    m = m/2;
  }
  j += m;
  //Danielson-Lanzcos routine
  mmax = 2;
  while(n > mmax){
    istep = mmax << 1;
    theta = isign*(2*pi/mmax);
    wtemp = sin(0.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi=sin(theta);
    wr=1.0;
    wi=0.0;
    //internal loops
    for (m = 1; m < mmax; m+=2){
      for(i = m; i <= n; i+=istep){
        j = i + mmax;
        tempr=wr*data[j-1]-wi*data[j];
        tempi=wr*data[j]+wi*data[j-1];
        data[j-1]=data[i-1]-tempr;
        data[j]=data[i]-tempi;
        data[i-1] += tempr;
        data[i] += tempi;
      }
      wr=(wtemp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtemp*wpi+wi;
    }
    mmax=istep;
  }
  return data;
}

