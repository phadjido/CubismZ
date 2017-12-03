# File       : Makefile
# Created    : Wed Nov 29 2017 07:34:13 PM (+0100)
# Author     : Fabian Wermelinger
# Description: Build CubismZ tools
# Copyright 2017 ETH Zurich. All Rights Reserved.
MYHDF = '-I/home/fabs/local/hdf5/build-parallel/include -L/home/fabs/local/hdf5/build-parallel/lib'

all: thirdparty

thirdparty:
	cd ThirdParty && ./build_all.sh

clean:
	rm -rf ThirdParty/build
