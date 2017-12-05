#!/bin/bash
set -x #echo on

h5file=../Data/data_005000-p.h5

if [ -z "$1" ]
then
	echo "setting err=0.01"
	err=0.01
else
	err=$1
fi

bs=32
ds=512
nb=$(echo "$ds/$bs" | bc)
wt=3
rm -f tmp.cz

../../Tools/bin/wavz_zlib/hdf2cz -bpdx $nb -bpdy $nb -bpdz $nb -sim io -simdata $h5file -outdata tmp.cz  -threshold $err -wtype_write $wt

mpirun -n 8 ../../Tools/bin/wavz_zlib/cz2diff -simdata1 tmp.cz  -simdata2 ref.cz -wtype $wt
