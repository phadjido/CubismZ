#!/usr/bin/env bash
# File       : build_all.sh
# Created    : Wed Nov 29 2017 07:04:15 PM (+0100)
# Author     : Fabian Wermelinger
# Description: Build Tools utilities
# Copyright 2017 ETH Zurich. All Rights Reserved.
BUILD="$(pwd -P)/build"
rm -rf ${BUILD}
mkdir -p "${BUILD}/bin"

movebin()
{
    cp "$@" "${BUILD}/bin"
}

root="$(pwd -P)"
###############################################################################
make -B -C ch2ch/ CC=mpic++ "$@" fpzip=1
movebin ch2ch/ch2ch*
make -C ch2ch/ clean

###############################################################################
make -B -C ch2dat/ CC=mpic++ "$@"
movebin ch2dat/ch2dat
make -C ch2dat/ clean

###############################################################################
make -B -C ch2diff/ CC=mpic++ "$@"
movebin ch2diff/ch2diff
make -C ch2diff/ clean

###############################################################################
make -B -C ch2hdf/ CC=mpic++ "$@"
movebin ch2hdf/ch2hdf ch2hdf/ch2roi
make -C ch2hdf/ clean

###############################################################################
make -B -C dataf/ CC=mpic++ "$@"
movebin dataf/compdat dataf/compdat2 dataf/printdat dataf/printdat_stride dataf/writedat
make -C dataf/ clean

###############################################################################
make -B -C vp2bin/ CC=mpic++ "$@"
movebin vp2bin/compbin vp2bin/diffbin vp2bin/printbin vp2bin/testbin vp2bin/vp2bin
make -C vp2bin/ clean

exit 0
