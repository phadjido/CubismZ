make clean;make wavz=1 zlib=1
make data_generator
./data_generator
./tests 
../tools/ch2hdf -simdata output00000.StreamerGridPointIterative.channel0 -h5file out1
#paraview out1.xmf
