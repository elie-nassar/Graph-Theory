CXX = g++
CXXFLAGS = -std=c++20 -Wall -O2

.PHONY: all
all: main

.PHONY: clean
clean:
	rm main *.o

main: main.o graph.o node.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<