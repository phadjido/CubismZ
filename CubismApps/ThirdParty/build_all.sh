#!/usr/bin/env bash
# File       : build_all.sh
# Created    : Wed Nov 29 2017 03:21:22 PM (+0100)
# Author     : Fabian Wermelinger
# Description: Build all third-party packages
# Copyright 2017 ETH Zurich. All Rights Reserved.
BUILD="$(pwd -P)/build"
rm -rf ${BUILD}
mkdir -p ${BUILD}/lib
mkdir -p ${BUILD}/include
mkdir -p ${BUILD}/bin

movelib()
{
    cp "$@" "${BUILD}/lib"
}
moveheader()
{
    dst="$1"; shift
    mkdir -p "${BUILD}/include/${dst}"
    cp "$@" "${BUILD}/include/${dst}"
}

root="$(pwd -P)"

###############################################################################
# fpzip-1.1.0
cd fpzip-1.1.0/src
make
cd ..
movelib lib/*.a
moveheader 'fpzip' inc/*
cd src
make cleanall
cd ${root}

###############################################################################
# lz4
cd lz4
make
movelib *.a
moveheader 'lz4' *.h
make clean
cd ${root}

###############################################################################
# SZ
cd SZ
bash make_sz "${BUILD}"
cd ${root}

###############################################################################
# zfp-0.5.0
cd zfp-0.5.0
make
movelib lib/libzfp.a
moveheader 'zfp' inc/*.h
make clean
cd ${root}

###############################################################################

exit 0
