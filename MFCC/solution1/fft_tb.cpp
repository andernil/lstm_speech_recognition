#include "../hamming_original.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

complex<double> wav_data[NUM_SAMPLES];
double golden_mels[NUM_FRAMES][MEL_NUM_FILTERBANKS];
complex<double> test_data[NUM_SAMPLES];

double avg_accuracy = 0;
double curr_accuracy = 0;
double min_accuracy = 1;
int accuracy_place[2];
int num_wav_samples_read = 0;


double temp_data = 0;
string read_buffer;

int main()
{
	int ret = 1;
	cout << "Current working directory " << endl;
	cout << system("pwd") << endl;
	// Load test data
	ifstream testData ("wav_data.dat");
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
	else{
		cout << "Failed to open wav-data file" << endl;
		return(ret);
	}
	// Load golden MFCC reference
	ifstream goldenMFCC ("golden_mel.dat");
	int num_mels_read = 0;
	if(goldenMFCC.is_open())
	{
		for(int mel_row = 0; mel_row < NUM_FRAMES; mel_row++)
		{
			for(int mel_num = 0; mel_num < MEL_NUM_FILTERBANKS; mel_num++){
				getline(goldenMFCC, read_buffer, '\n');
				temp_data = stod(read_buffer);
				golden_mels[mel_row][mel_num] = temp_data;
				//cout << "Row: " << mfcc_row << ". Num: " << mfcc_num << ". Val: " << golden_MFCC[mfcc_row][mfcc_num] << endl;
				num_mels_read++;
			}
		}
		cout << "Loaded " << num_mels_read << " golden mel values" << endl;
	}
	else{
		cout << "Failed to open MFCC file" << endl;
		return(ret);
	}
	testData.close();
	goldenMFCC.close();

	int peak_val = 0;
	cout << "Starting test" << endl;
	// Scale input to be within the range of -1 to +1
	for(int i = 0; i < NUM_SAMPLES; i++){
		test_data[i] = wav_data[i].real();
		if(hls::abs(test_data[i].real() > peak_val))
			peak_val = hls::abs(test_data[i].real());
	}
	double energies[NUM_FRAMES][MEL_NUM_FILTERBANKS];
	cout << "Running MFCC" << endl;
	MFCC_main(test_data, energies, peak_val);
	cout << "Done MFCC" << endl;
	for(int i = 0; i < NUM_FRAMES; i++)
	{
		for(int j = 0; j < MEL_NUM_FILTERBANKS; j++)
		{
			curr_accuracy = (energies[i][j]/ golden_mels[i][j]);
			if(curr_accuracy > 1)
				curr_accuracy = 1 / curr_accuracy;
			avg_accuracy += curr_accuracy;
			if(curr_accuracy < min_accuracy){
				min_accuracy = curr_accuracy;
				accuracy_place[0] = i;
				accuracy_place[1] = j;
			}
			cout << "[" << i << ", " << j << "]: " << "Calc: " <<  energies[i][j]
			     << ", Ref: " << golden_mels[i][j] << ", Accuracy: " << 100 * curr_accuracy << "%" << endl;
		}
	}
	avg_accuracy = 100 * avg_accuracy / (NUM_MEL_BANKS_TOTAL);
	//cout << "Average accuracy: " << avg_accuracy << "%" << endl;
	cout << "Minimum accuracy: " << 100 * min_accuracy << "% at " << accuracy_place[0] << ", " << accuracy_place[1] << endl;
	if(avg_accuracy > 85){
		ret = 0;
		cout << "Test passed, accuracy: " << avg_accuracy << "%" << endl;
	}
	else
		cout << "Test failed, accuracy: " << avg_accuracy << "%" << endl;
	return(ret);
}
