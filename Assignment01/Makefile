SANFLAGS = -fsanitize=address
CXXFLAGS = -Wall -std=c++17 -g $(SANFLAGS)
LDFLAGS = $(SANFLAGS)
a01:	a01.o wav-file.o
	g++ -o $@ $^ $(LDFLAGS)