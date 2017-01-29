#If the processor type is in "big endian", please set testdataDir to testdata/ppc instead. See testdata/README for details.
testdataDir=testdata/x86
make clean
make
./testdouble_compress sz.config $testdataDir/testdouble_8_8_128.dat 8 8 128
./testdouble_decompress sz.config $testdataDir/testdouble_8_8_128.dat.sz 8 8 128
./testfloat_compress sz.config $testdataDir/testfloat_8_8_128.dat 8 8 128
./testfloat_decompress sz.config $testdataDir/testfloat_8_8_128.dat.sz 8 8 128

