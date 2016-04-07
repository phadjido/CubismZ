# module load hdf5-parallel/1.8.11
CC = mpic++
#CC = CC
bs = 32
hdf = 1
include ../../Makefile.config 

CPPFLAGS += -I../reader 
CPPFLAGS += $(extra)

#CSCS
#CPPFLAGS += -I${HDF5_INCLUDE_OPTS}

#ifeq "$(zlib)" "1"
#	MYFLAGS += -D_USE_ZLIB_
#endif
#
#ifeq "$(lz4)" "1"
#	MYFLAGS += -D_USE_LZ4_  
#endif    

all: vp2hdf vp2roi

vp2hdf: main.o WaveletCompressor.o
	$(CC) $(CPPFLAGS) WaveletCompressor.o  main.o  -o vp2hdf $(LIBS) -ldl

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp -o main.o 
# -ldl
	
vp2roi: main_roi.o WaveletCompressor.o
	$(CC) $(CPPFLAGS) WaveletCompressor.o  main_roi.o  -o vp2roi $(LIBS) -ldl

main_roi.o: main_roi.cpp
	$(CC) $(CPPFLAGS) -c main_roi.cpp -o main_roi.o

WaveletCompressor.o: ../../MPCFnode/source/WaveletCompressor.cpp
	$(CC) $(CPPFLAGS) -c ../../MPCFnode/source/WaveletCompressor.cpp -o WaveletCompressor.o
	
clean:
	rm -f vp2hdf vp2roi *.o

cleanall:
	rm -f vp2hdf vp2roi *.o
