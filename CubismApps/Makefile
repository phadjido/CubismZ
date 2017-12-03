# File       : Makefile
# Created    : Wed Nov 29 2017 07:34:13 PM (+0100)
# Author     : Fabian Wermelinger
# Description: Build CubismZ tools
# Copyright 2017 ETH Zurich. All Rights Reserved.
MYHDF = '-I/home/fabs/local/hdf5/build-parallel/include -L/home/fabs/local/hdf5/build-parallel/lib'

all: thirdparty tools
#compression stage-1 (floating point)
wavz ?= 0

fpzip ?= 0
fpzip_eps ?= 32
zerobits ?= 0
zfp ?= 0
sz ?= 0

#compression stage-2 (encoding)
zlib ?= 0
lz4 ?= 0

# shuffling before encoding

shuffle3 ?= 0	# for wavz + shuffle3

tools: thirdparty
#	cd Tests && ./build_all.sh \
#		wavz=$(wavz) \
#		fpzip=$(fpzip) \
#		fpzip_eps=$(fpzip_eps) \
#		shuffle=$(shuffle) \
#		zerobits=$(zerobits) \
#		zfp=$(zfp) \
#		sz=$(sz) \
#		zlib=$(zlib) \
#		lz4=$(lz4) \
#		zshuffle=$(zshuffle) \
#		shuffle3=$(shuffle3) \
#		extra=$(MYHDF)

thirdparty:
	cd ThirdParty && ./build_all.sh

clean:
	rm -rf ThirdParty/build
