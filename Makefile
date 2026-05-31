TARGET_MAIN = bin/main
TARGET_TEST = bin/test

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -Iinclude

SRCS = src/graph.cpp src/coloring/proper_coloring.cpp src/sat.cpp src/binary_tree.cpp
OBJS = $(SRCS:src/%.cpp=build/%.o)

all: $(TARGET_MAIN)

$(TARGET_MAIN): $(OBJS) src/main.cpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(OBJS) $(TESTS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(OBJS) tests/test_graph.cpp tests/test_proper_coloring.cpp tests/test_binary_tree.cpp tests/test_global.cpp

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build bin

.PHONY: all test clean