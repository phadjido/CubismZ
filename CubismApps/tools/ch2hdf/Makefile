# module load hdf5-parallel/1.8.11
CC = mpic++
#CC = CC
bs = 32
hdf = 1
include ../../Makefile.config 

CPPFLAGS += -I../reader 
CPPFLAGS += $(extra)

# CSCS
#CPPFLAGS += -I${HDF5_INCLUDE_OPTS}

# BULLDOZER
#CPPFLAGS += -I${HOME}/usr/hdf5/include
#LIBS += -L${HOME}/usr/hdf5/lib -ldl

# PANDA
LIBS += -ldl

# JUQUEEN
#CPPFLAGS += -I/bgsys/local/hdf5/include
#LIBS += -L/bgsys/local/hdf5/lib -L/bgsys/local/szip/lib/ -lsz

# TUKEY
#CPPFLAGS += -I${HDF5_HOME}/include
#LIBS += -L${HDF5_HOME}/lib

#CPPFLAGS += -I${HOME}/usr_tukey/include
#LIBS += -L${HOME}/usr_tukey/lib

# CETUS
#CPPFLAGS += -I/soft/libraries/hdf5/current/cnk-xl/current/include
#LIBS += -L/soft/libraries/hdf5/current/cnk-xl/current/lib

#LIBS = $(LDFLAGS)
#ifeq "$(zlib)" "1"
#	MYFLAGS += -D_USE_ZLIB_
#endif
#
#ifeq "$(lz4)" "1"
#	MYFLAGS += -D_USE_LZ4_  
#endif    

all: ch2hdf ch2roi

ch2hdf: main.o WaveletCompressor.o
	$(CC) $(CPPFLAGS) WaveletCompressor.o  main.o  -o ch2hdf $(LIBS)

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp -o main.o
	
ch2roi: main_roi.o WaveletCompressor.o
	$(CC) $(CPPFLAGS) WaveletCompressor.o  main_roi.o  -o ch2roi $(LIBS)

main_roi.o: main_roi.cpp
	$(CC) $(CPPFLAGS) -c main_roi.cpp -o main_roi.o

WaveletCompressor.o: ../../MPCFnode/source/WaveletCompressor.cpp
	$(CC) $(CPPFLAGS) -c ../../MPCFnode/source/WaveletCompressor.cpp -o WaveletCompressor.o
	
clean:
	rm -f ch2hdf ch2roi *.o *.lst

cleanall:
	rm -f ch2hdf ch2roi *.o *.lst
