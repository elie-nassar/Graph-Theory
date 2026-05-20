CXX = g++
CXXFLAGS = -std=c++20 -Wall -O2 -Iinclude

APP_SRC = $(filter-out src/main.cpp, $(wildcard src/*.cpp))
APP_OBJ = $(APP_SRC:src/%.cpp=build/%.o)
MAIN_OBJ = build/main.o

BIN = bin/main
TEST_BIN = bin/tests_run
TEST_SRC = $(wildcard tests/*.cpp) $(APP_SRC)

all: $(BIN)

$(BIN): $(APP_OBJ) $(MAIN_OBJ)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test:
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf build bin