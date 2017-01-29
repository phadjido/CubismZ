## * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
##   Makefile to test SZ library.

##   PLEASE SET THIS VARIABLE BEFORE COMPILING
SZPATH = /home/chatzidp/DRain_membuffer/soft/SZ-0.5.14
JAVAHOME = /usr/lib/jvm/java-1.8.0-openjdk-1.8.0.77-0.b03.el7_2.x86_64
##   COMPILERS
CC		= gcc
FT		= gfortran
MPICC 		= mpicc
MPIRUN 		= mpirun

##   FLAGS
# Compiling using shared library
#SZFLAG 	= -I$(SZPATH)/include -L$(SZPATH)/lib -lsz
# Compiling using static library
SZFLAG 	= -I$(SZPATH)/include $(SZPATH)/SZ/lib/libsz.a
JAVAFLAG = -fPIC -I$(JAVAHOME)/include -I$(JAVAHOME)/include/linux -L$(JAVAHOME)/jre/lib/amd64/server -ljvm

##   TARGETS
all: 		testfloat_compress testfloat_decompress testdouble_compress testdouble_decompress testdouble_compress_f testdouble_decompress_f

testfloat_compress:	testfloat_compress.c
	$(CC) -g -o testfloat_compress testfloat_compress.c $(SZFLAG) $(JAVAFLAG)

testfloat_decompress:	testfloat_decompress.c
	$(CC) -g -o testfloat_decompress testfloat_decompress.c $(SZFLAG) $(JAVAFLAG)

testdouble_compress:	testdouble_compress.c
	$(CC) -g -o testdouble_compress testdouble_compress.c $(SZFLAG) $(JAVAFLAG)

testdouble_decompress:	testdouble_decompress.c
	$(CC) -g -o testdouble_decompress testdouble_decompress.c $(SZFLAG) $(JAVAFLAG)

testdouble_compress_f:      testdouble_compress.f90
	$(FT) -g -o testdouble_compress_f testdouble_compress.f90 $(SZFLAG) $(JAVAFLAG)
testdouble_decompress_f:      testdouble_decompress.f90
	$(FT) -g -o testdouble_decompress_f testdouble_decompress.f90 $(SZFLAG) $(JAVAFLAG)
clean:
	rm -f test*_compress test*_decompress test*_compress_f test*_decompress_f

