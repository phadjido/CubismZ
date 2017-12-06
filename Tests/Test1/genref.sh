#!/bin/bash
#
# genref.sh
# CubismZ
#
# Copyright 2017 ETH Zurich. All rights reserved.
#
set -x #echo on

h5file=../Data/data_005000-p.h5

bs=32
ds=512
nb=$(echo "$ds/$bs" | bc)

rm -f ref.cz

../../Tools/bin/default/hdf2cz -bpdx $nb -bpdy $nb -bpdz $nb -sim io -simdata $h5file  -outdata ref.cz
