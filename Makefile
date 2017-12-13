# File       : Makefile
# Created    : Wed Nov 29 2017 07:34:13 PM (+0100)
# Description: Build CubismZ tools
# Copyright 2017 ETH Zurich. All Rights Reserved.

###############################################################################
# User options
MPICC ?= mpic++
mpicc ?= mpicc
config ?= release
#hdf-incdir ?= /opt/hdf5_mpich/include
#hdf-libdir ?= /opt/hdf5_mpich/lib
# hdf-inc ?= /Users/phadjido/usr/hdf5/include
# hdf-lib ?= /Users/phadjido/usr/hdf5/lib
hdf-inc ?= /Users/fabs/local/hdf5/build-parallel/include
hdf-lib ?= /Users/fabs/local/hdf5/build-parallel/lib
hdf-libraries ?= -lhdf5

# general software configuration options
bs ?= 32
ap ?= float
omp ?= 1
needs_lz ?= 1

# options for the first compression stage (floating point)
wavz ?= 0
fpzip ?= 0
zfp ?= 0
sz ?= 0

# options for the second compression stage (encoding)
zlib ?= 0
lz4 ?= 0

# options (bit zeroing, byte shuffling) for the wavelet coefficients, applied between the first and second stage
zerobits ?= 0	# for wavz + zerobits
shuffle3 ?= 0	# for wavz + shuffle3
###############################################################################


###############################################################################
# Main rules
include Makefile.config
export

all: tools

tools: thirdparty-libs tools-only

tools-only:
	$(MAKE) -C Tools/ install dir=default
	$(MAKE) -C Tools/ install dir=wavz_zlib wavz=1 zlib=1
	$(MAKE) -C Tools/ install dir=fpzip fpzip=1
	$(MAKE) -C Tools/ install dir=zfp zfp=1
	$(MAKE) -C Tools/ install dir=sz sz=1

tools-custom:
	$(MAKE) -C Tools/ install

thirdparty-libs:
	$(MAKE) -C ThirdParty/

clean:
	$(MAKE) -C Tools/ clean
	$(MAKE) -C ThirdParty/ clean
###############################################################################
