CC = g++
CFLAGS = -Wall -std=c++11

all: scrabble_objects.o wordChecker.o
	$(CC) $(CFLAGS) -o scrabble scrabble_objects.o wordChecker.o

scrabble_objects.o: scrabble_objects.cpp 
	$(CC) $(CFLAGS) -c scrabble_objects.cpp

wordChecker.o: wordChecker.cpp 
	$(CC) $(CFLAGS) -c wordChecker.cpp

clean:
	rm -f *.o scrabble
