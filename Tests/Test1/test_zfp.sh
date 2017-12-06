#!/bin/bash
#
# test_zfp.sh
# CubismZ
#
# Copyright 2017 ETH Zurich. All rights reserved.
#
set -x #echo on

h5file=../Data/data_005000-p.h5

if [ -z "$1" ]
then
	echo "setting err=0.5"
	err=0.5
else
	err=$1
fi

bs=32
ds=512
nb=$(echo "$ds/$bs" | bc)

rm -f tmp.cz

../../Tools/bin/zfp/hdf2cz -bpdx $nb -bpdy $nb -bpdz $nb -sim io -simdata $h5file  -outdata tmp.cz  -threshold $err

mpirun -n 8 ../../Tools/bin/zfp/cz2diff -simdata1 tmp.cz  -simdata2 ref.cz
