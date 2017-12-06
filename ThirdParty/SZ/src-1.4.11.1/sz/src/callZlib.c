/**
 *  @file callZlib.c
 *  @author Sheng Di
 *  @date June, 2016
 *  @brief gzip compressor code: the interface to call zlib
 *  (C) 2016 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */


#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <zutil.h>
#include <sz.h>

#define CHECK_ERR(err, msg) { \
    if (err != Z_OK && err != Z_STREAM_END) { \
        fprintf(stderr, "%s error: %d\n", msg, err); \
        return SZ_NSCS; \
    } \
}

/*zlib_compress() is only valid for median-size data compression. */
unsigned long zlib_compress(unsigned char* data, unsigned long dataLength, unsigned char** compressBytes, int level)
{
	unsigned long outSize = dataLength;
	
	z_stream stream = {0};

    stream.next_in = data;
    stream.avail_in = dataLength;
#ifdef MAXSEG_64K
    /* Check for source > 64K on 16-bit machine: */
    if ((uLong)stream.avail_in != dataLength) return Z_BUF_ERROR;
#endif

    uLong estCmpLen = deflateBound(&stream, dataLength);	
	
	*compressBytes = (unsigned char*)malloc(sizeof(unsigned char)*estCmpLen);
	int err = compress2(*compressBytes, &outSize, data, dataLength, level);
	//printf("err=%d\n", err);
	return outSize;
}

unsigned long zlib_compress2(unsigned char* data, unsigned long dataLength, unsigned char** compressBytes, int level)
{
	unsigned long outSize;
	
	z_stream stream = {0};
    int err;

    stream.next_in = data;
    stream.avail_in = dataLength;
#ifdef MAXSEG_64K
    /* Check for source > 64K on 16-bit machine: */
    if ((uLong)stream.avail_in != dataLength) return Z_BUF_ERROR;
#endif

    uLong estCmpLen = deflateBound(&stream, dataLength);
	*compressBytes = (unsigned char*)malloc(sizeof(unsigned char)*estCmpLen);

    stream.next_out = *compressBytes;
    stream.avail_out = estCmpLen;
    //stream.avail_out = dataLength*10;
    //if ((uLong)stream.avail_out != dataLength*10) return Z_BUF_ERROR;

    stream.zalloc = (alloc_func)0;
    stream.zfree = (free_func)0;
    stream.opaque = (voidpf)0;
//	stream.data_type = Z_TEXT;

    //err = deflateInit(&stream, level); //default  windowBits == 15.
    int windowBits = 14; //8-15
    if(szMode==SZ_BEST_COMPRESSION)
		windowBits = 15;
	
    err = deflateInit2(&stream, level, Z_DEFLATED, windowBits, DEF_MEM_LEVEL,
                         Z_DEFAULT_STRATEGY);//Z_FIXED); //Z_DEFAULT_STRATEGY
    if (err != Z_OK) return err;

    err = deflate(&stream, Z_FINISH);
    if (err != Z_STREAM_END) {
        deflateEnd(&stream);
        return err == Z_OK ? Z_BUF_ERROR : err;
    }

    err = deflateEnd(&stream);
    
    outSize = stream.total_out;
    return outSize;
}

unsigned long zlib_compress3(unsigned char* data, unsigned long dataLength, unsigned char* compressBytes, int level)
{
	unsigned long outSize = 0;

	z_stream stream = {0};
    int err;

    stream.next_in = data;
    stream.avail_in = dataLength;
#ifdef MAXSEG_64K
    /* Check for source > 64K on 16-bit machine: */
    if ((uLong)stream.avail_in != dataLength) return Z_BUF_ERROR;
#endif

    stream.next_out = compressBytes;
    stream.avail_out = dataLength;
    stream.zalloc = (alloc_func)0;
    stream.zfree = (free_func)0;
    stream.opaque = (voidpf)0;

    //err = deflateInit(&stream, level); //default  windowBits == 15.
    int windowBits = 14; //8-15
    if(szMode==SZ_BEST_COMPRESSION)
		windowBits = 15;

    err = deflateInit2(&stream, level, Z_DEFLATED, windowBits, DEF_MEM_LEVEL,
                         Z_DEFAULT_STRATEGY);//Z_FIXED); //Z_DEFAULT_STRATEGY
    if (err != Z_OK) return err;

    err = deflate(&stream, Z_FINISH);
    if (err != Z_STREAM_END) {
        deflateEnd(&stream);
        return err == Z_OK ? Z_BUF_ERROR : err;
    }

    err = deflateEnd(&stream);

    outSize = stream.total_out;
    return outSize;
}

unsigned long zlib_compress4(unsigned char* data, unsigned long dataLength, unsigned char** compressBytes, int level)
{
	int err = 0;
	unsigned long outSize = 0;
	
	z_stream stream = {0};
 
    stream.next_in = data;
    stream.avail_in = dataLength;

    uLong estCmpLen = deflateBound(&stream, dataLength);
	*compressBytes = (unsigned char*)malloc(sizeof(unsigned char)*estCmpLen);	
	
	err = compress(*compressBytes, &outSize, data, dataLength);
	CHECK_ERR(err, "compress");
	
	
	return outSize;
}

unsigned long zlib_compress5(unsigned char* data, unsigned long dataLength, unsigned char** compressBytes, int level)
{
    z_stream c_stream = {0}; /* compression stream */
    int err = 0;

    c_stream.zalloc = (alloc_func)0;
    c_stream.zfree = (free_func)0;
    c_stream.opaque = (voidpf)0;

    int windowBits = 14; //8-15
    if(szMode==SZ_BEST_COMPRESSION)
		windowBits = 15;
    
    err = deflateInit2(&c_stream, level, Z_DEFLATED, windowBits, DEF_MEM_LEVEL,
                         Z_DEFAULT_STRATEGY);//Z_FIXED); //Z_DEFAULT_STRATEGY
    CHECK_ERR(err, "deflateInit");

    uLong estCmpLen = deflateBound(&c_stream, dataLength);
	*compressBytes = (unsigned char*)malloc(sizeof(unsigned char)*estCmpLen);	

    c_stream.next_in  = data;
    c_stream.next_out = *compressBytes;

    while (c_stream.total_in < dataLength && c_stream.total_out < estCmpLen) {
        c_stream.avail_in = c_stream.avail_out = SZ_ZLIB_BUFFER_SIZE; /* force small buffers */
        err = deflate(&c_stream, Z_NO_FLUSH);
        CHECK_ERR(err, "deflate");
    }
    /* Finish the stream, still forcing small buffers: */
    for (;;) {
        c_stream.avail_out = 1;
        err = deflate(&c_stream, Z_FINISH);
        if (err == Z_STREAM_END) break;
        CHECK_ERR(err, "deflate");
    }

    err = deflateEnd(&c_stream);
    CHECK_ERR(err, "deflateEnd");
    
    return c_stream.total_out;	
}

unsigned long zlib_uncompress(unsigned char* compressBytes, unsigned long cmpSize, unsigned char** oriData, unsigned long targetOriSize)
{
	unsigned long outSize;
	unsigned long* outSize_ = (unsigned long*)malloc(sizeof(unsigned long));
	*oriData = (unsigned char*)malloc(sizeof(unsigned char)*targetOriSize);
	uncompress(*oriData, outSize_, compressBytes, cmpSize); 
	outSize = *outSize_;
	free(outSize_);
	return outSize;
}

unsigned long zlib_uncompress2 (unsigned char* compressBytes, unsigned long cmpSize, unsigned char** oriData, unsigned long targetOriSize)
{
    z_stream stream = {0};

	unsigned long outSize;
	*oriData = (unsigned char*)malloc(sizeof(unsigned char)*targetOriSize);

    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
//	stream.data_type = Z_TEXT;

    stream.next_in = compressBytes;
    stream.avail_in = cmpSize;
    /* Check for source > 64K on 16-bit machine: */
    if ((unsigned long)stream.avail_in != cmpSize) 
    {
		printf("Error: zlib_uncompress2: stream.avail_in != cmpSize");
		//exit(1);
		return SZ_NSCS; //-1
	}

    stream.next_out = *oriData;
    stream.avail_out = targetOriSize;
    //if ((uLong)stream.avail_out != *destLen) return Z_BUF_ERROR;

    int err = inflateInit(&stream);
    //int windowBits = 15;
    //int err = inflateInit2(&stream, windowBits);
    if (err != Z_OK)
    {
		printf("Error: zlib_uncompress2: err != Z_OK\n");
		return SZ_NSCS;
	}

    err = inflate(&stream, Z_FINISH);
    if (err != Z_STREAM_END) {
        inflateEnd(&stream);
        if (err == Z_NEED_DICT || (err == Z_BUF_ERROR && stream.avail_in == 0))
            return Z_DATA_ERROR;
        return err;
    }
    outSize = stream.total_out;
    inflateEnd(&stream);
    return outSize;
}

unsigned long zlib_uncompress4(unsigned char* compressBytes, unsigned long cmpSize, unsigned char** oriData, unsigned long targetOriSize)
{
	int err;
	unsigned long uncomprLen;
	
	*oriData = (unsigned char*)malloc(sizeof(unsigned char)*targetOriSize);	
	
	err = uncompress(*oriData, &uncomprLen, compressBytes, cmpSize);
	CHECK_ERR(err, "uncompress");
	
	return uncomprLen;
}

unsigned long zlib_uncompress5(unsigned char* compressBytes, unsigned long cmpSize, unsigned char** oriData, unsigned long targetOriSize)
{
	int err;
	z_stream d_stream = {0}; /* decompression stream */

	*oriData = (unsigned char*)malloc(sizeof(unsigned char)*targetOriSize);		

    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;

	d_stream.next_in  = compressBytes;
	d_stream.avail_in = 0;
	d_stream.next_out = *oriData;

	err = inflateInit(&d_stream);
	CHECK_ERR(err, "inflateInit");

	while (d_stream.total_out < targetOriSize && d_stream.total_in < cmpSize) {
		d_stream.avail_in = d_stream.avail_out = SZ_ZLIB_BUFFER_SIZE; /* force small buffers */
		err = inflate(&d_stream, Z_NO_FLUSH);
		if (err == Z_STREAM_END) break;
		CHECK_ERR(err, "inflate");
	}

	err = inflateEnd(&d_stream);
	CHECK_ERR(err, "inflateEnd");

	return d_stream.total_out;
}

