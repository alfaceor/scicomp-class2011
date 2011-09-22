# Author: Carlos Olivares
# e-mail: alfaceor@gmail.com
CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lgsl -lgslcblas -lm
SRC_DIR=src
BUILD_DIR=build
SOURCE=gsl_example.c
EXECUTABLE=$(BUILD_DIR)/gsl_example.exe


all: $(EXECUTABLE)

$(EXECUTABLE):gsl_example.o
	$(CC) gsl_example.o $(LDFLAGS) -o $(EXECUTABLE)

gsl_example.o:$(SRC_DIR)/$(SOURCE)
	$(CC) $(CFLAGS) $(SRC_DIR)/$(SOURCE)

clean:
	rm -rf *.o $(EXECUTABLE)