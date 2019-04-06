# Makefile.config
# CubismZ
#
# Copyright 2018 ETH Zurich. All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
#
VERSION = 1.0.0

SHELL := /bin/bash

mpi_info = $(shell $(MPICXX) -show)
compiler = $(notdir $(firstword $(mpi_info)))
$(info Found [$(compiler)])

###############################################################################
# Compilation and linking options

ifeq "$(precision)" "float"
        CUBISMZFLAGS += -D_FLOAT_PRECISION_
endif

ifeq "$(config)" "release"
	CUBISMZFLAGS += -DNDEBUG -O3
else
	CUBISMZFLAGS += -g
endif

ifeq "$(omp)" "1"
	ifneq "$(compiler)" "clang++"
		CUBISMZFLAGS += -fopenmp
	endif
endif

CUBISMZFLAGS += -D_BLOCKSIZE_=$(blocksize) -D_BLOCKSIZEX_=$(blocksize) -D_BLOCKSIZEY_=$(blocksize) -D_BLOCKSIZEZ_=$(blocksize)
CUBISMZFLAGS += -I../Compressor/Cubism/source/ -I../Compressor/source/

CUBISMZFLAGS += -I$(hdf-incdir) -D_USE_HDF_
CUBISMZLIBS += -L$(hdf-libdir) $(hdf-libs)
CUBISMZLIBS += -lm

# ThirdParty libraries
CUBISMZFLAGS += -I../ThirdParty/build/include
CUBISMZLIBS += -L../ThirdParty/build/lib


CUBISMZFLAGS += $(extra)

###############################################################################
# Main rules
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
