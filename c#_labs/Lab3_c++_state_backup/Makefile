# Variables to control Makefile operation
CC=g++
CFLAGS=-I. -Wall -g

# The build target 
TARGET = myprogram
all: $(TARGET)

# Targets needed to bring the executable up to date
$(TARGET): main.o GameStarter.o Game.o ConcreteGameStates.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o GameStarter.o Game.o ConcreteGameStates.o

# The main.o target can be written more simply
main.o: main.cpp GameStarter.cpp Game.cpp ConcreteGameStates.cpp
	$(CC) $(CFLAGS) -c main.cpp

GameStarter.o: GameStarter.cpp
Game.o: Game.cpp
ConcreteGameStates.o: ConcreteGameStates.cpp

clean:
	$(RM) $(TARGET)
	# Optionally remove object files...
	$(RM) *.o

install: $(TARGET)
