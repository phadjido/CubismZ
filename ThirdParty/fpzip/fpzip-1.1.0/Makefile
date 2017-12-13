.PHONY: clean

all:
	$(MAKE) -C src/ CXX=$(CC)
	mkdir -p ../../build/include/fpzip
	mkdir -p ../../build/lib
	cp inc/* ../../build/include/fpzip
	cp lib/* ../../build/lib

clean:
	$(MAKE) -C src/ clean
