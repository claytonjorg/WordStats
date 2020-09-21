CC = g++
FLAGS = -std=c++11 -Wall
INC = -I Include

all: wordstats.x

wordstats.x: main.o
	$(CC) $(FLAGS) -o wordstats.x main.o
main.o: main.cpp
	$(CC) -c $(FLAGS) $(INC) main.cpp
