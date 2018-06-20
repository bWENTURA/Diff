OBJECTS = main.cpp functions.cpp longest_sequence.cpp
CFLAGS = -std=c++11 -g -Wall

all:
	g++ $(OBJECTS) $(CFLAGS) -o diff
