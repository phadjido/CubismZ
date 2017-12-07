#!/bin/bash
#
# test_sz.sh
# CubismZ
#
# Copyright 2017 ETH Zurich. All rights reserved.
#
set -x #echo on

h5file=../Data/data_005000-p.h5

nproc=1
if [ "$#" -eq 1 ]
then
    nproc=$1
fi

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

rm -f tmp.cz

mpirun -n 1 ../../Tools/bin/sz/hdf2cz -bpdx $nb -bpdy $nb -bpdz $nb -sim io -simdata $h5file  -outdata tmp.cz  -threshold $err

mpirun -n $nproc ../../Tools/bin/sz/cz2diff -simdata1 tmp.cz -simdata2 ref.cz
