# Variables to control Makefile operation
CC=g++
CFLAGS=-Wall -g
# Targets needed to bring the executable up to date
main: main.o other.o
	$(CC) $(CFLAGS) -o main main.o other.o
# The main.o target can be written more simply
main.o: main.cpp other.h
	$(CC) $(CFLAGS) -c main.cpp
other.o: other.h
