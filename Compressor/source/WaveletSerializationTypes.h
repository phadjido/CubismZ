/*
 * WaveletSerializationTypes.h
 * CubismZ
 *
 * Copyright 2018 ETH Zurich. All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef _WAVELETSERIALIZATIONTYPES_H_
#define _WAVELETSERIALIZATIONTYPES_H_ 1

#pragma once

struct BlockMetadata { int idcompression, subid, ix, iy, iz; }  __attribute__((packed));
struct HeaderLUT { size_t aggregate_bytes; int nchunks; }  __attribute__((packed));
struct CompressedBlock{ size_t start, extent; int subid; }  __attribute__((packed));

#endif
