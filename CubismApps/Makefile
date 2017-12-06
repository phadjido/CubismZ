# File       : Makefile
# Created    : Wed Nov 29 2017 07:34:13 PM (+0100)
# Author     : Fabian Wermelinger
# Description: Build CubismZ tools
# Copyright 2017 ETH Zurich. All Rights Reserved.
CC = mpic++
cc = mpicc
blocksize ?= 32

all: tools

tools: #thirdparty
	$(MAKE) -C Tools/ install CC=$(CC) bs=$(blocksize) dir=default
	$(MAKE) -C Tools/ install CC=$(CC) bs=$(blocksize) dir=wavz_zlib wavz=1 zlib=1
	$(MAKE) -C Tools/ install CC=$(CC) bs=$(blocksize) dir=fpzip fpzip=1
	$(MAKE) -C Tools/ install CC=$(CC) bs=$(blocksize) dir=zfp zfp=1
	$(MAKE) -C Tools/ install CC=$(CC) bs=$(blocksize) dir=sz sz=1

thirdparty:
	$(MAKE) -C ThirdParty/ CC=$(CC) cc=$(cc)

clean:
	$(MAKE) -C Tools/ clean
	$(MAKE) -C ThirdParty/ clean
