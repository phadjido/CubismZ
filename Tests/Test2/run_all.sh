#!/usr/bin/env bash
# File       : run_all.sh
# Created    : Thu Dec 07 2017 12:29:17 PM (+0100)
# Author     : Fabian Wermelinger
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
command -v mpirun >/dev/null 2>&1 || { echo >&2 "Can not find 'mpirun' command. Aborting."; exit 1; }
command -v bc >/dev/null 2>&1 || { echo >&2 "Can not find 'bc' command. Aborting."; exit 1; }

# wavelets + zlib
mymsg 'test_wavz.sh' >> $fout
./test_wavz.sh $nproc >> $fout

exit 0
