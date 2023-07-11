# Variables to control Makefile operation
CC=g++
CFLAGS=-Wall -g

# The build target 
TARGET = myprogram
all: $(TARGET)

# Targets needed to bring the executable up to date
$(TARGET): main.o point.o square.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o point.o square.o

# The main.o target can be written more simply
main.o: main.cpp Point.h Square.h
	$(CC) $(CFLAGS) -c main.cpp

Point.o: point.h
Square.o: square.h point.h

clean:
	$(RM) $(TARGET)
