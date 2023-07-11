# Variables to control Makefile operation
CC=g++
CFLAGS=-Wall -g

# The build target 
TARGET = lightprogram
all: $(TARGET)

# Targets needed to bring the executable up to date
$(TARGET): Main.o Light.o ConcreteLightStates.o
	$(CC) $(CFLAGS) -o $(TARGET) Main.o Light.o ConcreteLightStates.o

# The main.o target can be written more simply
main.o: main.cpp Light.cpp ConcreteLightStates.cpp
	$(CC) $(CFLAGS) -c main.cpp

Light.o: Light.cpp
ConcreteLightStates.o: ConcreteLightStates.cpp

clean:
	$(RM) $(TARGET)
