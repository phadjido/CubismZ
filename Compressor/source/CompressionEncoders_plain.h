/*
 * CompressionEncoders_plain.h
 * CubismZ
 *
 * Copyright 2017 ETH Zurich. All rights reserved.
 */

#ifndef _COMPRESSIONENCODERS_PLAIN_H_
#define _COMPRESSIONENCODERS_PLAIN_H_ 1

#include <zlib.h>	// always needed

inline int deflate_inplace(z_stream *strm, unsigned char *buf, unsigned len, unsigned *max);
inline size_t zdecompress(unsigned char * inputbuf, size_t ninputbytes, unsigned char * outputbuf, const size_t maxsize);


inline size_t zdecompress_plain(unsigned char * inputbuf, size_t ninputbytes, unsigned char * outputbuf, const size_t maxsize)
{
	int decompressedbytes = 0;

	decompressedbytes = ninputbytes;
	memcpy(outputbuf, inputbuf, ninputbytes);

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
