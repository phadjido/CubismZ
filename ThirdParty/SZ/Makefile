.PHONY: clean

base = $(realpath .)

all:
	cd src-1.4.11.1; ./configure CC=$(MPICC) --prefix=$(base)/../build --disable-shared
	cd src-1.4.11.1; $(MAKE) install

clean:
	-cd src-1.4.11.1; $(MAKE) distclean
