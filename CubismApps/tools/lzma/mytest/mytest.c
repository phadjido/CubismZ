/*
 * Written in 2009 by Lloyd Hilaiel
 *
 * License
 * 
 * All the cruft you find here is public domain.  You don't have to credit
 * anyone to use this code, but my personal request is that you mention
 * Igor Pavlov for his hard, high quality work.
 *
 * Various compiled-in tests for the easylzma library which excercise
 * API correctness and handling of corrupt data.
 */


#include "easylzma.c"

#include <stdio.h>
#include <string.h>

int main(void)
{
    unsigned int i;
    int rc = 0;

#define N (32*1024)
    float in[N];
    float *out;

    printf("round trip lzma test:\n ");
    fflush(stdout);

    unsigned char * compressed;
    unsigned char * decompressed;
    size_t ins = N*sizeof(float), outs, outs2;

    for (i = 0; i < N; i++) in[i] = i*1.0;
    
    rc = simpleCompress(ELZMA_lzma, (unsigned char *) in, ins, &compressed, &outs);

    printf("compression: %ld -> %ld\n", ins, outs);
 
    if (rc != ELZMA_E_OK) return rc;

    rc = simpleDecompress(ELZMA_lzma, compressed, outs, &decompressed, &outs2);

    printf("decompression: %ld -> %ld\n", outs, outs2);

    free(compressed);

    out = (float *) decompressed;
    for (i = 0; i < N; i+=1024) {
	printf("dec[%4d] = %f\n", i, out[i]);
    }


    if (rc != ELZMA_E_OK) return rc;
    
    return ELZMA_E_OK;
}
