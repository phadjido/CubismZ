.PHONY: clean fpzip sz zfp zlib

all: fpzip lzfour sz zfp zlib

fpzip:
	$(MAKE) -C fpzip/ CC=$(MPICC)

lzfour:
	$(MAKE) -C lz4/ CC=$(mpicc) cc=$(mpicc)

sz:
	$(MAKE) -C SZ/ CC=$(mpicc) cc=$(mpicc)

zfp:
	$(MAKE) -C zfp/ CC=$(MPICC) cc=$(mpicc)

zlib:
	$(MAKE) -C zlib/

clean:
	rm -rf build
	$(MAKE) -C fpzip/ clean
	$(MAKE) -C lz4/ clean
	$(MAKE) -C zfp/ clean
	$(MAKE) -C zlib/ clean
	$(MAKE) -C SZ/ clean
