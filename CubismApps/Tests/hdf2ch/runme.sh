bs=32
ds=512
nb=$(echo "$ds/$bs" | bc)

make clean

#make all wavz=1 zlib=1
#make all wavz=1 lzma=1
make all wavz=1 lzma=1 shuffle=1
#make all wavz=1 lzma=1 shuffle=1 zerobits=8
#make all fpzip=1
#make all zfp=1
#make all sz=1
#make all isa=1


rm tmp00000.StreamerGridPointIterative.channel0

./hdf2ch -bpdx $nb -bpdy $nb -bpdz $nb -sim io -simdata data-301-g.h5  -outdata tmp  -threshold 0.008 -wtype_write 3

mpirun -n 8 ./ch2diff -simdata1 tmp00000.StreamerGridPointIterative.channel0  -simdata2 ref.channel0 -wtype 3

