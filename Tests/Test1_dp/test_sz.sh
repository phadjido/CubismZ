#!/usr/bin/env bash
# test_sz.sh
# CubismZ
#
# Copyright 2018 ETH Zurich. All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
#
set -x #echo on

[[ ! -f ../Data/demo_dp.h5 ]] && tar -C ../Data -xJf ../Data/data.tar.xz
h5file=../Data/demo_dp.h5

if [ -z ${1+x} ]
then
    echo "setting err=0.0001"
    err=0.0001
else
    err=$1
    if [ "$1" -eq "-1" ]; then
        echo "setting err=0.0001"
        err=0.0001
    fi
    shift
fi

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
mpirun -n 1 ../../Tools/bin/sz/hdf2cz -bpdx $nb -bpdy $nb -bpdz $nb -sim io -h5file $h5file  -czfile tmp.cz  -threshold $err

mpirun -n $nproc ../../Tools/bin/sz/cz2diff -czfile1 tmp.cz -czfile2 ref.cz
