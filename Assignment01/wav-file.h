#ifndef WAV_FILE_HH
#define WAV_FILE_HH

#include <string>

/*
 * Given a filename to a .wav file, returns by reference:
 * - the length of the audio, measured in the number of samples
 * - the sampling rate. I.e., the number of samples per second
 */
void wav_file_info(std::string, size_t*, unsigned long*);

// fills up the given array with sample data from the given .wav file
void wav_file_data(std::string filename, short*, size_t offset, size_t len);

#endif
