#include <iostream>
#include "wav-file.h"
#include <string>
#include <cmath>
#include <iomanip>

// void wav_file_info(std::string, size_t*, unsigned long*);

// fills up the given array with sample data from the given .wav file
// void wav_file_data(std::string filename, short*, size_t offset, size_t len);

using namespace std;        // 이거로 std::string의 std 생략.

// times = array, 
size_t find_silence(string filename, double* times, size_t max_n) {     // max_n = len 넣으면 될 것으로 보임
    size_t length;             // 실제 .wav 파일 길이 -> len과 다름 -> len보다 크거나 같아야 함.
    unsigned long sampling_rate; // sampling 속도 -> 44100이 나옴.
    short data[5000];          // 데이터 개수 -> 넉넉히 만 개, 교수님 추천 few thousand 라서
    size_t off = 0;             // 데어터 읽기 시작 위치 설정용              // MAX amplitude 설정용
    size_t count = 0;           // 0.5초 silence 측정용 -> 1초 = 44100 -> 0.5초 = 22050개
    size_t t_count = 0;
    size_t amp = 0;
    int final = 0;
    wav_file_info(filename, &length, &sampling_rate); // 1차 제공 코드 이용
    cout << length << " , " << sampling_rate << '\n';

    // 여기에 while문 추가로 off 증가 고민
    while (true) {
        wav_file_data(filename, data, off, max_n);

        // 이 밑에 data 분석하는 코드 작성하면 됨.
        for (size_t i = 0; i < max_n; i++) {
            if (data[i] == -32768)  // abs 안 통하는 경우 예외 처리.
                amp = 32767;
            else 
                if (abs(data[i]) > amp) {
                    amp = abs(data[i]);
                }
            if (abs(data[i]) <= 1000)        // 시간 확인 i - n + 1
                count += 1;
            else {
//                while (times[t_count] >= 10000) -> 소수점 앞 5자리 넘어가는 경우 해결되면 작성.
                if (count >= sampling_rate / 2 and t_count < 10) {
                    times[t_count] = static_cast<double>(off+i-count)/sampling_rate;
                    t_count += 1;
                }
                count = 0;
            }
        }
        cout << off << '\n';
        if (final == 1)
            break;
        off += max_n;
        if (off >= length-max_n){
            max_n = length-off;
            final += 1;
        }
    }

    // times에 amp를 넣으면 뒤에 .0000이 왜인지는 모르겠지만 붙음. 아마 setprecision하면 
    cout << "Peak amplitude: " << amp <<'\n';
    cout << "Periods of silence:\n";
    for (size_t i = 0; i < t_count; i++) {
        cout << setw(9) << fixed << setprecision(4) << times[i] << '\n';       // 기본값 소숫점 6개라서 변경함.
    }
    cout << off << " , " << max_n << " , " << off + max_n << '\n';
    return t_count;
}
// 일단 재귀 없이 시도. 굳이 최적화 하고 싶으면 find_silence 안에 또 함수 넣어서 거기에 off 변수로 넣을 수 있는 방법 채용하기.



int main () {
    string filename;            // 불러올 .wav 파일 이름
    double times[10] = {-1};
    size_t max_n = 5000;         // len 만든 이유 여기서 data 크기 변경 못해서 그런 걸로 보이기는 함.

    printf("Enter filename: ");
    cin >> filename;            // 파일 이름 입력
    find_silence(filename, times, max_n);

    return 0;
}

/* 필요 시 Makefile 에 추가.
a01_simul:	a01_simul.o wav-file.o
	g++ -o $@ $^ $(LDFLAGS)
*/