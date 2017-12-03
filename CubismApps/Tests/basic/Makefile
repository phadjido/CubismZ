SHELL := /bin/bash

CC = mpic++
bs ?= 32
ap ?= float
hdf ?= 1
config ?=release

include ../../Makefile.config

nchannels ?= 1
CPPFLAGS += -DTOTAL_CHANNELS=$(nchannels)

# PANDA
LIBS += -ldl

CPPFLAGS += -I../../../Cubism/source/ -I../../Compressor/source -I. -I../../Compressor/reader

##################
VPATH := ../../../Cubism/source/ ../../Compressor/source/ ../source

all: tests data_generator

tests: main.o WaveletCompressor.o
	$(CC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

data_generator: data_generator.cpp
	$(CC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC)  $(OPTFLAGS) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f *.o tests tests data_generator out* in.dat
