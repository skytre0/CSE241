#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    if (a >= b) {
        printf("%d \n", (a-b));
    }
    else {
        printf("%d \n", (b-a));
    }
    return 0;
}

/* Assignment00's Makefile
CXXFLAGS = -Wall -std=c++14 -g
do:	Assignment00.o
	g++ -o $@ $^
*/
