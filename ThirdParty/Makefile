.PHONY: clean fpzip sz zfp zlib

all: fpzip lzfour sz zfp zlib

fpzip:
	$(MAKE) -C fpzip/ CC=$(CC)

lzfour:
	$(MAKE) -C lz4/ CC=$(cc) cc=$(cc)

sz:
	$(MAKE) -C SZ/ CC=$(cc) cc=$(cc)

zfp:
	$(MAKE) -C zfp/ CC=$(CC) cc=$(cc)

zlib:
	$(MAKE) -C zlib/ 

clean:
	rm -rf build
	$(MAKE) -C fpzip/ clean
	$(MAKE) -C lz4/ clean
	$(MAKE) -C zfp/ clean
	$(MAKE) -C zlib/ clean
	$(MAKE) -C SZ/ clean
