SANFLAGS = -fsanitize=address
CXXFLAGS += -Wall -std=c++17 -g $(SANFLAGS)
LDFLAGS += $(SANFLAGS)
main:	main.o parse.o expr.o
	$(CXX) -o $@ $^ $(LDFLAGS)
main.o:	main.cc parse.h expr.h
parse.o:	parse.cc parse.h expr.h
expr.o:	expr.cc expr.h