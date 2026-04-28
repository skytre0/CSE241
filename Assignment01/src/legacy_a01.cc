#include <iostream>
#include <iomanip>
#include <algorithm>
#include "wav-file.h"

using namespace std;

static short peak_amplitude(string filename) {
	size_t num_samples;
	unsigned long sampling_rate;
	wav_file_info(filename, &num_samples, &sampling_rate);
	short sample_data[8000];
	size_t i = 0;
	short peak = 0;
	while (i < num_samples) {
		size_t samples_to_read = min(sizeof sample_data / sizeof sample_data[0], num_samples - i);
		wav_file_data(filename, sample_data, i, samples_to_read);
		i += samples_to_read;
		for (size_t j = 0; j < samples_to_read; j++)
			peak = max(peak, (short)abs(sample_data[j]));
	}
	return peak;
}

size_t find_silence(string filename, double* silences, size_t max_n) {
	size_t num_samples;
	unsigned long sampling_rate;
	wav_file_info(filename, &num_samples, &sampling_rate);
	short sample_data[8000];
	size_t i = 0;
	size_t silence_i = 0;
	bool in_silence = false;
	size_t cur_silence_start = 0;
	while (i < num_samples) {
		size_t samples_to_read = min(sizeof sample_data / sizeof sample_data[0], num_samples - i);
		wav_file_data(filename, sample_data, i, samples_to_read);
		for (size_t j = 0; j < samples_to_read; j++)
			if (in_silence && (abs(sample_data[j]) >= 1000 || i + j == num_samples - 1)) {
				in_silence = false;
				size_t cur_position = i + j;
				if ((cur_position - cur_silence_start) / (double)sampling_rate >= 0.5) {
					silences[silence_i] = cur_silence_start / (double)sampling_rate;
					silence_i++;
				}
			} else if (!in_silence && abs(sample_data[j] < 1000)) {
				in_silence = true;
				cur_silence_start = i + j;
			}
		i += samples_to_read;
		if (silence_i >= max_n)
			return silence_i;
	}
	return silence_i;
}

int main() {
	string filename;
	cout << "Enter filaneme: " << flush;
	cin >> filename;
	cout << "Peak amilptude: " << peak_amplitude(filename) << endl;
	double silence_starts[10];
	size_t num_silence;
	num_silence = find_silence(filename, silence_starts, sizeof silence_starts / sizeof silence_starts[0]);
	for (size_t i = 0; i < num_silence; i++)
		cout << fixed << setw(7) << setprecision(4) << silence_starts[i] << '\n';
	return 0;
}
