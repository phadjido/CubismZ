# File       : Makefile
# Created    : Wed Nov 29 2017 07:34:13 PM (+0100)
# Author     : Fabian Wermelinger
# Description: Build CubismZ tools
# Copyright 2017 ETH Zurich. All Rights Reserved.
MYHDF = '-I/home/fabs/local/hdf5/build-parallel/include -L/home/fabs/local/hdf5/build-parallel/lib'

#compression stage-1 (floating point)
wavz ?= 0

fpc ?= 0
fpzip ?= 0
fpzip_eps ?= 32
shuffle ?= 0
zerobits ?= 0
zfp ?= 0
sz ?= 0
isa ?= 0

#compression stage-2 (encoding)
zlib ?= 0
lz4 ?= 0
lzf ?= 0
zstd ?= 0
zstd0 ?=0

# shuffling before encoding
zshuffle ?= 0

spdp3 ?= 0	# for wavz + spdp
fpzip3 ?= 0	# for wavz + fpz
zfp3 ?= 0	# for wavz + zfp
sz3 ?= 0	# for wavz + sz
fpc3 ?= 0	# for wavz + fpc
shuffle3 ?= 0	# for wavz + shuffle3

all: tools

tools: thirdparty
	cd Tools && ./build_all.sh \
		wavz=$(wavz) \
		fpc=$(fpc) \
		fpzip=$(fpzip) \
		fpzip_eps=$(fpzip_eps) \
		shuffle=$(shuffle) \
		zerobits=$(zerobits) \
		zfp=$(zfp) \
		sz=$(sz) \
		isa=$(isa) \
		zlib=$(zlib) \
		lz4=$(lz4) \
		lzf=$(lzf) \
		zstd=$(zstd) \
		zstd0=$(zstd0) \
		zshuffle=$(zshuffle) \
		spdp3=$(spdp3) \
		fpzip3=$(fpzip3) \
		zfp3=$(zfp3) \
		sz3=$(sz3) \
		fpc3=$(fpc3) \
		shuffle3=$(shuffle3) \
		extra=$(MYHDF)

thirdparty:
	cd ThirdParty && ./build_all.sh

clean:
	rm -rf ThirdParty/build
	rm -rf Tools/build
