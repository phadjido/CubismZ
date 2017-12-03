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

OBJECTS = main.o WaveletCompressor.o

all: tests

tests: $(OBJECTS)
	$(CC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC)  $(OPTFLAGS) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f *.o tests out1.h5 out1.xmf output00000.StreamerGridPointIterative.channel0
