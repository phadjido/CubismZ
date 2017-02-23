#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#include "myspdp.h"

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
	outs = spdp_compress_data( (const char*)indat, SZ*sizeof(dtype), (char *) outdat, SZ*sizeof(dtype)+1024);
	double t1 = omp_get_wtime();
	
        printf("outs = %ld\n", outs);
        printf("rate = %.2lf\n", (1.0*SZ*sizeof(dtype))/outs);
        printf("time = %.2lf s\n", t1-t0);

	outs2 = spdp_uncompress_data((const char*)outdat, outs, (char *) outdat2, SZ*sizeof(dtype));
        printf("outs2 = %ld\n", outs2);

        for (i = 0; i < SZ; i+=(SZ/4)) printf("%d : %lf vs %lf\n", i, indat_copy[i], outdat2[i]);
        for (i = SZ-3; i < SZ; i+=1) printf("%d : %lf vs %lf\n", i, indat_copy[i], outdat2[i]);

	return 0;
}
