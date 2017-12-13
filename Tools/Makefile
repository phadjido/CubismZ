SHELL := /bin/bash

dir ?= default

#################
# Fixed options
nchannels = 1
CUBISMZFLAGS += -DTOTAL_CHANNELS=$(nchannels)
CUBISMZFLAGS += -I../../Cubism/source/ -I../Compressor/source -I. -I../Compressor/reader
CUBISMZLIBS += -L../ThirdParty/build/lib
CUBISMZLIBS += -ldl

##################
# Makefile rules
.PHONY: .FORCE
VPATH := ../../Cubism/source/ ../Compressor/source/ .

all: hdf2cz cz2hdf cz2diff

hdf2cz: hdf2cz.o WaveletCompressor.o
	$(MPICC) $(extra) $^ -o $@ $(CUBISMZLIBS)

cz2hdf: cz2hdf.o WaveletCompressor.o
	$(MPICC) $(extra) $^ -o $@ $(CUBISMZLIBS)

cz2diff: cz2diff.o WaveletCompressor.o
	$(MPICC) $(extra) $^ -o $@ $(CUBISMZLIBS)

%.o: %.cpp .FORCE
	$(MPICC) $(CUBISMZFLAGS) -c $< -o $@

.FORCE:

install: all
	mkdir -p bin/$(dir)
	mv hdf2cz cz2hdf cz2diff bin/$(dir)
	rm -f *.o

clean:
	rm -rf bin
	rm -f *.o hdf2cz cz2hdf cz2diff
