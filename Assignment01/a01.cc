#include <iostream>
#include "wav-file.h"
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;


size_t find_silence(string filename, double* times, size_t max_n) {
    size_t length;
    unsigned long sampling_rate;
    short data[5000];
    size_t off = 0;
    size_t count = 0;
    size_t t_count = 0;
    size_t amp = 0;
    int final = 0;

    wav_file_info(filename, &length, &sampling_rate);

    while (true) {
        wav_file_data(filename, data, off, max_n);

        for (size_t i = 0; i < max_n; i++) {
            if (data[i] == -32768)
                amp = 32767;
            else 
                if (abs(data[i]) > amp) 
                    amp = abs(data[i]);
                
            if (abs(data[i]) <= 1000)
                count += 1;
            else {
                
                count = 0;
            }
        }
        /*          말씀 없이 pdf 내용 바뀐 거 아마 해결책
        if (final == 1 || off + max_n == length) {
            if (count >= sampling_rate / 2 and t_count < 10) {
                    times[t_count] = static_cast<double>(off+max_n-1-count)/sampling_rate;
                }
            break;
        }
*/
        if (final == 1)
            break;

        off += max_n;

        if (off >= length-max_n){
            max_n = length-off;
            final += 1;
        }
    }

    cout << "Peak amplitude: " << amp <<'\n';
    cout << "Periods of silence:\n";
    for (size_t i = 0; i < t_count; i++) 
        cout << setw(9) << fixed << setprecision(4) << times[i] << '\n';
    
    return t_count;
}




int main () {
    string filename;
    double times[10] = {-1};
    size_t max_n = 5000;

    printf("Enter filename: ");
    cin >> filename;
    find_silence(filename, times, max_n);

    return 0;
}

