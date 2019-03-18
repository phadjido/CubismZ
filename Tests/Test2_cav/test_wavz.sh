#!/usr/bin/env bash
# test_wavz.sh
# CubismZ
#
# Copyright 2018 ETH Zurich. All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
#
set -x #echo on

[[ ! -f ../Data/data_005000-p.h5 ]] && (cd ../Data; ./get_cavitation_data.sh)
h5file=../Data/data_005000-p.h5

if [ -z "$2" ]
then
	echo "setting err=0.01"
	err=0.01
else
	err=$2
fi

nproc=1
if [ "$#" -eq 1 ]
then
    nproc=$1
fi

bs=32
ds=512
nb=$(echo "$ds/$bs" | bc)
wt=3
rm -f tmp.cz

export OMP_NUM_THREADS=$nproc
mpirun -n 1 ../../Tools/bin/wavz_zlib/hdf2cz -bpdx $nb -bpdy $nb -bpdz $nb -sim io -h5file $h5file -czfile tmp.cz -threshold $err -wtype $wt

# decompress and convert back to HDF5 (cz2hdf must have been compiled with the same options)
mpirun -n $nproc ../../Tools/bin/wavz_zlib/cz2hdf -czfile tmp.cz -wtype $wt -h5file out

# visualize with Paraview
# paraview out.xmf
