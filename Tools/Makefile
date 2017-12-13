SHELL := /bin/bash

#################
# Default options
dir ?= default

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
# Flags related to the compression options

ifeq "$(wavz)" "1"
       CUBISMZFLAGS += -D_USE_WAVZ_
endif

ifeq "$(fpzip)" "1"
	CUBISMZFLAGS += -D_USE_FPZIP_  -I../ThirdParty/build/include/fpzip
	CUBISMZLIBS += -lfpzip
endif

ifeq "$(zfp)" "1"
	CUBISMZFLAGS += -D_USE_ZFP_  -I../ThirdParty/build/include/zfp
	CUBISMZLIBS += -lzfp
endif

ifeq "$(sz)" "1"
	CUBISMZFLAGS += -D_USE_SZ_  -I../ThirdParty/build/include
	CUBISMZLIBS += -lSZ  -lzlib
	needs_lz = 0
endif


###############################################################################
# Flags related to the encoding options

ifeq "$(zlib)" "1"
	CUBISMZFLAGS += -D_USE_ZLIB_
	CUBISMZLIBS += -lz
endif

ifeq "$(lz4)" "1"
       CUBISMZFLAGS += -D_USE_LZ4_  -I../ThirdParty/build/include/lz4
       CUBISMZLIBS += -llz4
endif

ifeq "$(needs_lz)" "1"
	CUBISMZLIBS += -lz
endif

###############################################################################
# Flags related to the extensions to the wavelet-based compression (wavz)

ifeq "$(shuffle3)" "1"
       CUBISMZFLAGS += -D_USE_SHUFFLE3_
endif

ifeq "$(zerobits)" "4"
       CUBISMZFLAGS += -D_USE_ZEROBITS_
       CUBISMZFLAGS += -D_ZEROBITS_=4
endif
ifeq "$(zerobits)" "8"
       CUBISMZFLAGS += -D_USE_ZEROBITS_
       CUBISMZFLAGS += -D_ZEROBITS_=8
endif
ifeq "$(zerobits)" "12"
       CUBISMZFLAGS += -D_USE_ZEROBITS_
       CUBISMZFLAGS += -D_ZEROBITS_=12
endif
ifeq "$(zerobits)" "16"
       CUBISMZFLAGS += -D_USE_ZEROBITS_
       CUBISMZFLAGS += -D_ZEROBITS_=16
endif

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
