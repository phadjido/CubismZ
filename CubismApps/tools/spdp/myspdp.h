#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
//#include <omp.h>

typedef unsigned char byte_t;
typedef unsigned int word_t;

extern "C"
{
extern size_t spdp_compress(const byte_t level, const size_t length, byte_t* const buf1, byte_t* const buf2);
extern void spdp_decompress(const byte_t level, const size_t length, byte_t* const buf2, byte_t* const buf1);
}

static size_t spdp_compress_data( const char* buffIn, size_t buffInSize, char* buffOut, size_t buffOutSize )
{
	int clevel = 5;

	char *ptr = &buffOut[0];

	size_t csize;

	memcpy(ptr, &buffInSize, sizeof(buffInSize));
	ptr += sizeof(buffInSize);

	csize = 0;
	memcpy(ptr, &csize, sizeof(csize));
	char *ptr_csize = ptr;
	ptr += sizeof(csize);

	csize = spdp_compress(clevel, buffInSize, (byte_t *)buffIn, (byte_t *)ptr); 	//buffOut);
	ptr += csize;

	size_t total_size = csize; // + 2*sizeof(size_t);
	memcpy(ptr_csize, &total_size, sizeof(total_size));

	return csize;
}

static size_t spdp_uncompress_data( const char* buffIn, size_t buffInSize, char* buffOut, size_t buffOutSize)
{
	int clevel = 5;

	size_t dsize, csize;
	char *ptr = (char *)&buffIn[0];

	memcpy(&dsize, ptr, sizeof(dsize));
	ptr += sizeof(dsize);

	memcpy(&csize, ptr, sizeof(csize));
	ptr += sizeof(csize);

	printf("UncompressData: dsize = %ld, csize = %ld\n", dsize, csize);
	//csize = csize - 2*sizeof(size_t);

	spdp_decompress(clevel, csize, (byte_t *)ptr, (byte_t *)buffOut);
	return dsize;
}


#if 0

#ifndef dtype
#define dtype double
#endif

#ifndef SZ
#define SZ1	32
#define SZ	(SZ1*SZ1*SZ1)
#endif

static dtype indat[SZ];
static dtype indat_copy[SZ];
static dtype outdat[SZ+1024];
static dtype outdat2[SZ];

int main(int argc, char *argv[])
{
        size_t outs;
        size_t outs2;

        int i;
	//for (i = 0; i < SZ; i++) indat[i] = exp(-i);
	srand48(1);
	for (i = 0; i < SZ; i++) indat[i] = 1.20+drand48();
	for (i = 0; i < SZ; i++) indat_copy[i] = indat[i];

	double t0 = omp_get_wtime();
	outs = CompressData( (const char*)indat, SZ*sizeof(dtype), (char *) outdat, SZ*sizeof(dtype)+1024);
	double t1 = omp_get_wtime();
	
        printf("outs = %ld\n", outs);
        printf("rate = %.2lf\n", (1.0*SZ*sizeof(dtype))/outs);
        printf("time = %.2lf s\n", t1-t0);

	outs2 = UncompressData((const char*)outdat, outs, (char *) outdat2, SZ*sizeof(dtype));
        printf("outs2 = %ld\n", outs2);

        for (i = 0; i < SZ; i+=(SZ/4)) printf("%d : %lf vs %lf\n", i, indat_copy[i], outdat2[i]);
        for (i = SZ-3; i < SZ; i+=1) printf("%d : %lf vs %lf\n", i, indat_copy[i], outdat2[i]);

	return 0;
}

#endif
