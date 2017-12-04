# File       : Makefile
# Created    : Wed Nov 29 2017 07:34:13 PM (+0100)
# Author     : Fabian Wermelinger
# Description: Build CubismZ tools
# Copyright 2017 ETH Zurich. All Rights Reserved.
all: tools

tools: #thirdparty
	$(MAKE) -C Tools/ install dir=default
	$(MAKE) -C Tools/ install dir=wavz_zlib wavz=1 zlib=1
	$(MAKE) -C Tools/ install dir=fpzip fpzip=1
	$(MAKE) -C Tools/ install dir=zfp zfp=1
	$(MAKE) -C Tools/ install dir=sz sz=1
	$(MAKE) -C Tools/ clean

thirdparty:
	cd ThirdParty && ./build_all.sh

clean:
	rm -rf Tools/bin
	rm -rf ThirdParty/build
