.PHONY: clean

cc = gcc
base = $(realpath .)

all:
	cd zlib-1.2.11; ./configure CC=$(cc) --prefix=$(base)/../build --static
	cd zlib-1.2.11; $(MAKE) install

clean:
	cd zlib-1.2.11; $(MAKE) distclean
