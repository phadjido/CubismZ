.PHONY: clean

base = $(realpath .)

all:
	cd zlib-1.2.11; CC=$(MPICC) ./configure --prefix=$(base)/../build --static
	cd zlib-1.2.11; $(MAKE) install

clean:
	-rm -f zlib-1.2.11/Makefile zlib-1.2.11/zconf.h
	-cd zlib-1.2.11; $(MAKE) distclean
