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
VPATH := ../../../Cubism/source/ ../../Compressor/source/ .


all: hdf2ch ch2hdf ch2diff decompr

hdf2ch: hdf2ch.o WaveletCompressor.o
	$(CC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

ch2hdf: ch2hdf.o WaveletCompressor.o
	$(CC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

ch2diff: ch2diff.o WaveletCompressor.o
	$(CC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

decompr: decompr.o WaveletCompressor.o
	$(CC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC)  $(OPTFLAGS) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f *.o hdf2ch ch2hdf ch2diff decompr

cleanall:
	rm -f *.o hdf2ch ch2hdf ch2diff decompr out*
