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

mpirun -n 1 ../../Tools/bin/wavz_zlib/hdf2cz -bpdx $nb -bpdy $nb -bpdz $nb -sim io -simdata $h5file -outdata compressed.cz  -threshold $err -wtype_write $wt

# decompresse and convert back to HDF5 (cz2hdf must have been compiled with the same options)
mpirun -n 8 ../../Tools/bin/wavz_zlib/cz2hdf -simdata compressed.cz  -h5file out1 -wtype $wt

# visualize with Paraview
# paraview out1.xmf