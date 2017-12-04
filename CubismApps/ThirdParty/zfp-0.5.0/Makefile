MAKEFLAGS += --no-print-directory

all: static
	mkdir -p ../build/include/zfp
	mkdir -p ../build/lib
	cp inc/*.h ../build/include/zfp
	cp lib/* ../build/lib

static:
	@cd src; $(MAKE) static cc=$(cc)
	@cd examples; $(MAKE) all CXX=$(CC) CC=$(cc)

shared:
	@cd src; $(MAKE) shared cc=$(cc)

test:
	@cd examples; $(MAKE) test

clean:
	@cd src; $(MAKE) clean
	@cd examples; $(MAKE) clean

