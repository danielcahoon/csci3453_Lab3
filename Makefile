CXX      := g++
CXXFLAGS := -std=c++11

ucd-csci3453-lab3: Page.o main.o 
	    $(CXX) $(CXXFLAGS)  -o ucd-csci3453-lab3 main.o Page.o

main.o: main.cpp Page.h
	    $(CXX) $(CXXFLAGS) -c -o main.o main.cpp

Page.o: Page.h Page.cpp
		$(CXX) $(CXXFLAGS) -c -o Page.o Page.cpp

.PHONY: clean test

clean:
	    rm -f Page.o main.o ucd-csci3453-lab3 output

test: ucd-csci3453-lab3
	    ./ucd-csci3453-lab3 128 pg-reference.txt output

test2: ucd-csci3453-lab3
	    ./ucd-csci3453-lab3 3 input.txt output
