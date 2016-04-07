# Compile
make clean;make CC=mpic++ wavz=0 drain=1 zlib=0 

# Get HDF5 file from another Test 
cp ../init/makefiles/out1.h5 .

# Compress HDF5
./hdf2ch -sim io -simdata out1.h5 -outdata out1toh5

# Convert back to HDF5 (decompress)
../../tools/ch2hdf/ch2hdf -simdata out1toh500000.StreamerGridPointIterative.channel0 -h5file out1back

