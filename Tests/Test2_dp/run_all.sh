#!/usr/bin/env bash
# run_all.sh
# CubismZ
#
# Copyright 2018 ETH Zurich. All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
#
nproc=1
if [[ "$#" -eq 1 ]]; then
    nproc=$1
fi

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
mymsg 'test_wavz.sh'
./test_wavz.sh $nproc

exit 0
