zlib = 0
include ../../Makefile.config


ifeq "$(bgq)" "1"
AR = /bgsys/drivers/ppcfloor/gnu-linux/bin/powerpc64-bgq-linux-ar
CPPFLAGS += -qpack_semantic=gnu
else
AR = ar
endif
ARFLAGS = rcs

.PHONY: clean

all: liblz4.a
	mkdir -p ../build/include/lz4
	mkdir -p ../build/lib
	cp lz4.h ../build/include/lz4
	cp liblz4.a ../build/lib

liblz4.a: lz4.o
	$(AR) $(ARFLAGS) liblz4.a lz4.o

lz4.o: lz4.c lz4.h
	$(cc) $(CPPFLAGS) -c lz4.c

clean:
	rm -f *.o *.a
