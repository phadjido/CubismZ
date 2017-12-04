SHELL := /bin/bash

hdf = 1

include ../Makefile.config

CC = mpic++
cc = mpicc
dir ?= default
nchannels ?= 1

CPPFLAGS += -DTOTAL_CHANNELS=$(nchannels)
LIBS += -L../ThirdParty/build/lib

# PANDA
LIBS += -ldl

CPPFLAGS += -I../../Cubism/source/ -I../Compressor/source -I. -I../Compressor/reader

##################
.PHONY: clean
VPATH := ../../Cubism/source/ ../Compressor/source/ .


all: fpzip lz4 SZ zfp

fpzip:
	$(MAKE) -C fpzip-1.1.0/ CC=$(CC) cc=$(cc)

lz4:
	$(MAKE) -C lz4/ CC=$(CC) cc=$(cc)

SZ:
	$(MAKE) -C SZ/ CC=$(CC) cc=$(cc)

zfp:
	$(MAKE) -C zfp-0.5.0/ CC=$(CC) cc=$(cc)

clean:
	rm -rf build
	$(MAKE) -C fpzip-1.1.0/ clean
	$(MAKE) -C lz4/ clean
	$(MAKE) -C SZ/ clean
	$(MAKE) -C zfp-0.5.0/ clean
