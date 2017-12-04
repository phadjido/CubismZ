.PHONY: clean

base = $(realpath .)

all:
	mkdir -p build
	cd src-1.4.11.1; ./configure CC=$(cc) --prefix=$(base)/../build --disable-shared
	cd src-1.4.11.1; $(MAKE) install

clean:
	cd src-1.4.11.1; $(MAKE) distclean
