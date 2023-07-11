# Variables to control Makefile operation
CC=g++
CFLAGS=-I. -Wall -g

SRC = main.cpp adidas.cpp adidasShirt.cpp adidasShoe.cpp nike.cpp nikeShirt.cpp nikeShoe.cpp
OBJ = ${SRC:.cpp=.o}

# The build target 
TARGET = sportfactories
all: $(TARGET)

# Targets needed to bring the executable up to date
$(TARGET): ${OBJ}
	$(CC) $(CFLAGS) -o $(TARGET) ${OBJ}

clean:
	$(RM) $(TARGET)
	# Optionally remove object files...
	$(RM) *.o

install: $(TARGET)
