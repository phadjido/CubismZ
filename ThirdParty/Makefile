.PHONY: clean

all: fpzip lzfour sz1 zfp

fpzip:
	$(MAKE) -C fpzip-1.1.0/ CC=$(CC)

lzfour:
	$(MAKE) -C lz4/ CC=$(cc) cc=$(cc)

sz1:
	$(MAKE) -C SZ/ CC=$(cc) cc=$(cc)

zfp:
	$(MAKE) -C zfp-0.5.0/ CC=$(CC) cc=$(cc)

zlibrary:
	$(MAKE) -C zlib/ 

clean:
	rm -rf build
	$(MAKE) -C fpzip-1.1.0/ clean
	$(MAKE) -C lz4/ clean
	$(MAKE) -C SZ/ clean
	$(MAKE) -C zfp-0.5.0/ clean
	$(MAKE) -C zlib/ clean
