SHELL := /bin/bash

#################
# User options

MPICC ?= mpic++
config ?=release
dir ?= default

blocksize ?= 32
hdf-incdir ?= /opt/hdf5_mpich/include
hdf-libdir ?= /opt/hdf5_mpich/lib

#################
# Fixed options

hdf-inc = $(hdf-incdir)
hdf-lib = $(hdf-libdir)

include ../Makefile.config

nchannels = 1
CPPFLAGS += -DTOTAL_CHANNELS=$(nchannels)

CPPFLAGS += -I../../Cubism/source/ -I../Compressor/source -I. -I../Compressor/reader
LIBS += -L../ThirdParty/build/lib
LIBS += -ldl


##################
# Makefile rules

VPATH := ../../Cubism/source/ ../Compressor/source/ .


all: hdf2cz cz2hdf cz2diff

hdf2cz: hdf2cz.o WaveletCompressor.o
	$(MPICC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

cz2hdf: cz2hdf.o WaveletCompressor.o
	$(MPICC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

cz2diff: cz2diff.o WaveletCompressor.o
	$(MPICC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(MPICC) $(OPTFLAGS) $(CPPFLAGS) -c $^ -o $@

install: all
	mkdir -p bin/$(dir)
	mv hdf2cz cz2hdf cz2diff bin/$(dir)
	rm -f *.o

clean:
	rm -rf bin
	rm -f *.o hdf2cz cz2hdf cz2diff 
