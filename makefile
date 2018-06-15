OBJECTS = main.cpp functions.cpp longest_sequence.cpp
CFLAGS = -g -Wall

all:
	g++ $(OBJECTS) $(CFLAGS) -o diff
