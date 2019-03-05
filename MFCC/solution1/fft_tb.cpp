#include "../hamming_original.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

complex<double> wav_data[NUM_SAMPLES];
data_out_t golden_MFCC[NUM_FRAMES][NUM_MFCC_COEFFICIENTS];
cmpxDataIn test_data[NUM_SAMPLES];

double avg_accuracy = 0;
double curr_accuracy = 0;
double min_accuracy = 1;
int accuracy_place[2];
int num_wav_samples_read = 0;


double temp_data = 0;
string read_buffer;

int main()
{
	cout << "Current working directory " << endl;
	cout << system("pwd") << endl;
	// Load test data
	ifstream testData ("wavData.dat");
	if(testData.is_open())
	{
		for(num_wav_samples_read = 0; num_wav_samples_read < NUM_SAMPLES; num_wav_samples_read++)
		{
			getline(testData, read_buffer, '\n');
			wav_data[num_wav_samples_read] = stod(read_buffer);
			//if(num_wav_samples_read > 13824 && num_wav_samples_read < 14336)
				//cout << wav_data[num_wav_samples_read] << endl;
		}
		cout << endl;
		cout << "Loaded " << num_wav_samples_read << " samples from wav-file" << endl;
	}
	else
		cout << "Failed to open wav-data file" << endl;

	// Load golden MFCC reference
	ifstream goldenMFCC ("goldenMFCC.dat");

	if(goldenMFCC.is_open())
	{
		for(int mfcc_row = 0; mfcc_row < NUM_FRAMES; mfcc_row++)
		{
			for(int mfcc_num = 0; mfcc_num < NUM_MFCC_COEFFICIENTS; mfcc_num++){
				getline(goldenMFCC, read_buffer, '\n');
				temp_data = stod(read_buffer);
				golden_MFCC[mfcc_row][mfcc_num] = temp_data;
				//cout << "Row: " << mfcc_row << ". Num: " << mfcc_num << ". Val: " << golden_MFCC[mfcc_row][mfcc_num] << endl;
			}
		}
	}
	else
		cout << "Failed to open MFCC file" << endl;

	testData.close();
	goldenMFCC.close();

	cout << "Starting test" << endl;
	// Scale input to be within the range of -1 to +1
	for(int i = 0; i < NUM_SAMPLES; i++)
		test_data[i] = wav_data[i].real() / ((1 << 23) - 1); //2 << 14, 23 for correct peaks
	data_out_t energies[NUM_FRAMES][NUM_MFCC_COEFFICIENTS];
	cout << "Running MFCC" << endl;
	MFCC_main(test_data, energies, 48000);
	cout << "Done MFCC" << endl;

	for(int i = 0; i < NUM_FRAMES; i++)
	{
		for(int j = 0; j < NUM_MFCC_COEFFICIENTS; j++)
		{
			curr_accuracy = (energies[i][j]/ golden_MFCC[i][j]);
			if(curr_accuracy > 1)
				curr_accuracy = 1 / curr_accuracy;
			avg_accuracy += curr_accuracy;
			if(curr_accuracy < min_accuracy){
				min_accuracy = curr_accuracy;
				accuracy_place[0] = i;
				accuracy_place[1] = j;
			}
			cout << "[" << i << ", " << j << "]: " << "Calc: " <<  energies[i][j] << ", Ref: " << golden_MFCC[i][j] << ", Accuracy: " << curr_accuracy << endl;
		}
	}
	avg_accuracy = 100 * avg_accuracy / (NUM_FRAMES * NUM_MFCC_COEFFICIENTS);
	cout << "Average accuracy: " << avg_accuracy << "%" << endl;
	cout << "Minimum accuracy: " << 100 * min_accuracy << "% at " << accuracy_place[0] << ", " << accuracy_place[1] << endl;

	return(0);
}
