SHELL := /bin/bash

CC = mpic++
config ?=release
dir ?= default
hdf = 1
nchannels = 1

include ../Makefile.config

CPPFLAGS += -DTOTAL_CHANNELS=$(nchannels)
LIBS += -L../ThirdParty/build/lib
LIBS += -ldl

CPPFLAGS += -I../../Cubism/source/ -I../Compressor/source -I. -I../Compressor/reader

##################
VPATH := ../../Cubism/source/ ../Compressor/source/ .


all: hdf2cz cz2hdf cz2diff

hdf2cz: hdf2cz.o WaveletCompressor.o
	$(CC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

cz2hdf: cz2hdf.o WaveletCompressor.o
	$(CC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

cz2diff: cz2diff.o WaveletCompressor.o
	$(CC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC)  $(OPTFLAGS) $(CPPFLAGS) -c $^ -o $@

install: all
	mkdir -p bin/$(dir)
	mv hdf2cz cz2hdf cz2diff bin/$(dir)
	rm -f *.o

clean:
	rm -rf bin
	rm -f *.o hdf2cz cz2hdf cz2diff 
