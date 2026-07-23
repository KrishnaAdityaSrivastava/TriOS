CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -I.

SOURCES := trit/tryte.cpp \
	memory/memory.cpp \
	cpu/cpu.cpp \
	cpu/instructionHandler.cpp \
	cpu/register.cpp \
	assembler/assembler.cpp \
	assembler/assembleLoader.cpp \
	logic/gates.cpp \
	alu/alu.cpp

.PHONY: all test clean

all: trios

trios: main.cpp $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

tests/test_trios: tests/test_trios.cpp $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: tests/test_trios
	./tests/test_trios

clean:
	rm -f trios tests/test_trios
