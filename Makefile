# File       : Makefile
# Created    : Wed Nov 29 2017 07:34:13 PM (+0100)
# Description: Build CubismZ tools
# Copyright 2017 ETH Zurich. All Rights Reserved.

MPICC ?= mpic++
mpicc ?= mpicc
blocksize ?= 32
#hdf-incdir ?= /opt/hdf5_mpich/include
#hdf-libdir ?= /opt/hdf5_mpich/lib
hdf-incdir ?= /Users/phadjido/usr/hdf5/include
hdf-libdir ?= /Users/phadjido/usr/hdf5/lib
hdf-libs ?= -lhdf5_mpich
all: tools

tools: thirdparty-libs tools-only


tools-only:
	$(MAKE) -C Tools/ install MPICC=$(MPICC) bs=$(blocksize) hdf-inc=$(hdf-incdir) hdf-lib=$(hdf-libdir) hdf-libraries=$(hdf-libs) dir=default
	$(MAKE) -C Tools/ install MPICC=$(MPICC) bs=$(blocksize) hdf-inc=$(hdf-incdir) hdf-lib=$(hdf-libdir) hdf-libraries=$(hdf-libs) dir=wavz_zlib wavz=1 zlib=1
	$(MAKE) -C Tools/ install MPICC=$(MPICC) bs=$(blocksize) hdf-inc=$(hdf-incdir) hdf-lib=$(hdf-libdir) hdf-libraries=$(hdf-libs) dir=fpzip fpzip=1
	$(MAKE) -C Tools/ install MPICC=$(MPICC) bs=$(blocksize) hdf-inc=$(hdf-incdir) hdf-lib=$(hdf-libdir) hdf-libraries=$(hdf-libs) dir=zfp zfp=1
	$(MAKE) -C Tools/ install MPICC=$(MPICC) bs=$(blocksize) hdf-inc=$(hdf-incdir) hdf-lib=$(hdf-libdir) hdf-libraries=$(hdf-libs) dir=sz sz=1

thirdparty-libs:
	$(MAKE) -C ThirdParty/ CC=$(MPICC) cc=$(mpicc)

clean:
	$(MAKE) -C Tools/ clean
	$(MAKE) -C ThirdParty/ clean
