#!/usr/bin/env bash
# File       : run_all.sh
# Created    : Thu Dec 07 2017 12:29:17 PM (+0100)
# Description: Batch run all test cases.  The output is stored in run_all.txt
# Copyright 2017 ETH Zurich. All Rights Reserved.
nproc=1
if [[ "$#" -eq 1 ]]; then
    nproc=$1
fi

fout='run_all.txt'

mymsg()
{
    echo ''
    echo '###############################################################################'
    echo "RUNNING: $1"
    echo '###############################################################################'
    echo ''
}



# Test if dependencies are satisfied
use_awk=1
command -v mpirun >/dev/null 2>&1 || { echo >&2 "Can not find 'mpirun' command. Aborting."; exit 1; }
command -v bc >/dev/null 2>&1 || { echo >&2 "Can not find 'bc' command. Aborting."; exit 1; }
command -v awk >/dev/null 2>&1 || { echo >&2 "Can not find 'awk' command for filtered output."; use_awk=0; }

output_filter()
{
    if [ "$use_awk" -eq 1 ]; then
        awk '$0 ~ /(^Channel|^TLP|^Time distribution|^threads:|^Elapsed time|^compression-rate:|^RE.?:)/ { print $0; }' >> $fout
    else
        cat >> $fout
    fi
}

# generate reference
mymsg 'genref.sh' >> $fout
./genref.sh | output_filter

# wavelets + zlib
mymsg 'test_wavz.sh' >> $fout
./test_wavz.sh $nproc | output_filter

# zfp
mymsg 'test_zfp.sh' >> $fout
./test_zfp.sh $nproc | output_filter

# fpzip
mymsg 'test_fpzip.sh' >> $fout
./test_fpzip.sh $nproc | output_filter

# sz
mymsg 'test_sz.sh' >> $fout
./test_sz.sh $nproc | output_filter

rm -f tmp.cz
rm -f ref.cz

exit 0
