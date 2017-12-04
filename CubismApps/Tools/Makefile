SHELL := /bin/bash

CC = mpic++
config ?=release
dir ?= default

include ../Makefile.config

nchannels ?= 1
CPPFLAGS += -DTOTAL_CHANNELS=$(nchannels)
LIBS += -L../ThirdParty/build/lib
LIBS += -ldl

CPPFLAGS += -I../../Cubism/source/ -I../Compressor/source -I. -I../Compressor/reader

##################
VPATH := ../../Cubism/source/ ../Compressor/source/ .


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

install: all
	mkdir -p bin/$(dir)
	mv hdf2ch ch2hdf ch2diff decompr bin/$(dir)
	rm -f *.o

clean:
	rm -f *.o hdf2ch ch2hdf ch2diff decompr

cleanall:
	rm -f *.o hdf2ch ch2hdf ch2diff decompr out*
