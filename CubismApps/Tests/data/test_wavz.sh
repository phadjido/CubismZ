#!/bin/bash
set -x #echo on

if [ -z "$1" ]
then
    	echo "missing file"
        exit
else
    	h5file=$1
fi

bs=32
ds=512
nb=$(echo "$ds/$bs" | bc)
wt=3

(cd ../tools; make clean; make all wavz=1 zlib=1)

rm tmp00000.StreamerGridPointIterative.channel0

../tools/hdf2ch -bpdx $nb -bpdy $nb -bpdz $nb -sim io -simdata $h5file -outdata tmp  -threshold $2 -wtype_write $wt

mpirun -n 8 ../tools/ch2diff -simdata1 tmp00000.StreamerGridPointIterative.channel0  -simdata2 ref.channel0 -wtype $wt

