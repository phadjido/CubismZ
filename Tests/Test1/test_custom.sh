#!/usr/bin/env bash
# test_custom.sh
# CubismZ
#
# Copyright 2018 ETH Zurich. All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
#
set -x #echo on

[[ ! -f ../Data/demo.h5 ]] && tar -C ../Data -xJf ../Data/data.tar.xz
h5file=../Data/demo.h5

mypath="$1"; shift
thresh=$1; shift
nproc=1
if [ ! -z ${1+x} ]
then
    nproc=$1; shift
fi

bs=32
ds=128
nb=$(echo "$ds/$bs" | bc)

rm -f tmp.cz

# check if reference file exists, create it otherwise
if [ ! -f ref.cz ]
then
    ./genref.sh
fi

export OMP_NUM_THREADS=$nproc
mpirun -n 1 ${mypath}/hdf2cz -bpdx $nb -bpdy $nb -bpdz $nb -sim io -h5file $h5file -czfile tmp.cz -threshold $thresh

mpirun -n $nproc ${mypath}/cz2diff -czfile1 tmp.cz  -czfile2 ref.cz
