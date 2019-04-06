/*
 * CompressionEncoders_plain.h
 * CubismZ
 *
 * Copyright 2018 ETH Zurich. All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef _COMPRESSIONENCODERS_PLAIN_H_
#define _COMPRESSIONENCODERS_PLAIN_H_ 1

#include <cstring>
#include <zlib.h>	// always needed

inline int deflate_inplace(z_stream *strm, unsigned char *buf, unsigned len, unsigned *max);
inline size_t zdecompress(unsigned char * inputbuf, size_t ninputbytes, unsigned char * outputbuf, const size_t maxsize);


inline size_t zdecompress_plain(unsigned char * inputbuf, size_t ninputbytes, unsigned char * outputbuf, const size_t maxsize)
{
	int decompressedbytes = 0;

	decompressedbytes = ninputbytes;
    std::memcpy(outputbuf, inputbuf, ninputbytes);

	return decompressedbytes;
}

inline int deflate_inplace_plain(z_stream *strm, unsigned char *buf, unsigned len, unsigned *max)
{
	int compressedbytes = len;
	strm->total_out = compressedbytes;
	*max = compressedbytes;
        return Z_OK;
}

#endif
