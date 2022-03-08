.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -g

all: main

obj:
	mkdir -p obj

main: src/main.cpp obj/matrix.o include/*.h obj
	$(CXX) $(CXXFLAGS) -o lab-07_matrix -Iinclude $< obj/*

obj/%.o: src/%.cpp include/*.h obj
	$(CXX) $(CXXFLAGS) -c -o $@ -Iinclude $<

clean:
	rm -rf obj main
