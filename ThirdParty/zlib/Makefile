.PHONY: clean

base = $(realpath .)

all:
	cd zlib-1.2.11; CC=$(mpicc) ./configure --prefix=$(base)/../build --static
	cd zlib-1.2.11; $(MAKE) install

clean:
	-cd zlib-1.2.11; $(MAKE) distclean
