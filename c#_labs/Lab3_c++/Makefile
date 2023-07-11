# Variables to control Makefile operation
CC=g++
CFLAGS=-I. -Wall -g

SRC = main.cpp GameStarter.cpp Game.cpp ConcreteGameStates.cpp Player.cpp RandomPlaysGenerator.cpp
OBJ = ${SRC:.cpp=.o}

# The build target 
TARGET = myprogram
all: $(TARGET)

# Targets needed to bring the executable up to date
$(TARGET): ${OBJ}
	$(CC) $(CFLAGS) -o $(TARGET) ${OBJ}

clean:
	$(RM) $(TARGET)
	# Optionally remove object files...
	$(RM) *.o

install: $(TARGET)
