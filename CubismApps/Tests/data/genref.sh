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

rm -f ref.channel0

../../Tools/bin/default/hdf2ch -bpdx $nb -bpdy $nb -bpdz $nb -sim io -simdata $h5file  -outdata ref.cz

