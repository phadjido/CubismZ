.PHONY: clean fpzip sz zfp zlib

all: fpzip lzfour sz zfp zlib

fpzip:
	$(MAKE) -C fpzip/ CC=$(MPICXX)

lzfour:
	$(MAKE) -C lz4/ CC=$(MPICC) cc=$(MPICC)

sz:
	$(MAKE) -C SZ/ CC=$(MPICC) cc=$(MPICC)

zfp:
	$(MAKE) -C zfp/ CC=$(MPICXX) cc=$(MPICC)

zlib:
	$(MAKE) -C zlib/

clean:
	rm -rf build
	$(MAKE) -C fpzip/ clean
	$(MAKE) -C lz4/ clean
	$(MAKE) -C zfp/ clean
	$(MAKE) -C zlib/ clean
	$(MAKE) -C SZ/ clean
