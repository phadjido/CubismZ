SHELL := /bin/bash

#################
# User options

MPICC ?= mpic++
blocksize ?= 32
hdf-incdir ?= /Users/phadjido/usr/hdf5/include #. #/opt/hdf5_mpich/include
hdf-libdir ?= /Users/phadjido/usr/hdf5/lib #. #/opt/hdf5_mpich/lib

config ?=debug
dir ?= default

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

#LIBS += -L/usr/local/opt/zlib/lib
#CPPFLAGS += -I/usr/local/opt/zlib/include


##################
# Makefile rules
.PHONY: .FORCE
VPATH := ../../Cubism/source/ ../Compressor/source/ .


all: hdf2cz cz2hdf cz2diff

hdf2cz: hdf2cz.o WaveletCompressor.o
	$(MPICC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

cz2hdf: cz2hdf.o WaveletCompressor.o
	$(MPICC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

cz2diff: cz2diff.o WaveletCompressor.o
	$(MPICC) $(OPTFLAGS) $(extra) $^ -o $@ $(LIBS)

%.o: %.cpp .FORCE
	$(MPICC) $(OPTFLAGS) $(CPPFLAGS) -c $< -o $@

.FORCE:

install: all
	mkdir -p bin/$(dir)
	mv hdf2cz cz2hdf cz2diff bin/$(dir)
	rm -f *.o

clean:
	rm -rf bin
	rm -f *.o hdf2cz cz2hdf cz2diff
