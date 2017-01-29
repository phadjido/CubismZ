/**
 *  @file szf.c
 *  @author Sheng Di
 *  @date April, 2015
 *  @brief the key C binding file to connect Fortran and C
 *  (C) 2015 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sz.h"

void sz_init_c_(char *configFile,int *len,int *ierr){
    int i;
    char s2[*len+1];
    for(i=0;i<*len;i++)
        s2[i]=configFile[i];
    s2[*len]='\0';
 //   printf("sconfigFile=%s\n",configFile);
    *ierr = SZ_Init(s2);
}

void sz_finalize_c_()
{
	SZ_Finalize();
}

//file writing and reading interfaces
void SZ_writeData_inBinary_d1_Float_(float* data, char *fileName, int *len)
{
	int i;
    char s2[*len+1];
    for(i=0;i<*len;i++)
        s2[i]=fileName[i];
    s2[*len]='\0';
    
}

//compress with config (without args in function)

void sz_compress_d1_float_(float* data, char *bytes, int *outSize, int *r1)	
{
	char *tmp_bytes = SZ_compress(SZ_FLOAT, data, outSize, 0, 0, 0, 0, *r1);
	memcpy(bytes, tmp_bytes, *outSize);	
}

void sz_compress_d1_float_rev_(float* data, float *reservedValue, char *bytes, int *outSize, int *r1)	
{
	char *tmp_bytes = SZ_compress_rev(SZ_FLOAT, data, reservedValue, outSize, 0, 0, 0, 0, *r1);
	memcpy(bytes, tmp_bytes, *outSize);	
}

void sz_compress_d2_float_(float* data, float *reservedValue, char *bytes, int *outSize, int *r1, int *r2)
{
	char *tmp_bytes = SZ_compress(SZ_FLOAT, data, outSize, 0, 0, 0, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d2_float_rev_(float* data, float *reservedValue, char *bytes, int *outSize, int *r1, int *r2)
{
	char *tmp_bytes = SZ_compress_rev(SZ_FLOAT, data, reservedValue, outSize, 0, 0, 0, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d3_float_(float* data, char *bytes, int *outSize, int *r1, int *r2, int *r3)
{
	char *tmp_bytes = SZ_compress(SZ_FLOAT, data, outSize, 0, 0, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d3_float_rev_(float* data, float *reservedValue, char *bytes, int *outSize, int *r1, int *r2, int *r3)
{
	char *tmp_bytes = SZ_compress_rev(SZ_FLOAT, data, reservedValue, outSize, 0, 0, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d4_float_(float* data, char *bytes, int *outSize, int *r1, int *r2, int *r3, int *r4)
{
	char *tmp_bytes = SZ_compress(SZ_FLOAT, data, outSize, 0, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d4_float_rev_(float* data, float *reservedValue, char *bytes, int *outSize, int *r1, int *r2, int *r3, int *r4)
{
	char *tmp_bytes = SZ_compress_rev(SZ_FLOAT, data, reservedValue, outSize, 0, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d5_float_(float* data, char *bytes, int *outSize, int *r1, int *r2, int *r3, int *r4, int *r5)
{
	char *tmp_bytes = SZ_compress(SZ_FLOAT, data, outSize, *r5, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d5_float_rev_(float* data, float *reservedValue, char *bytes, int *outSize, int *r1, int *r2, int *r3, int *r4, int *r5)
{
	char *tmp_bytes = SZ_compress_rev(SZ_FLOAT, data, reservedValue, outSize, *r5, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d1_double_(double* data, char *bytes, int *outSize, int *r1)
{
	char *tmp_bytes = SZ_compress(SZ_DOUBLE, data, outSize, 0, 0, 0, 0, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d1_double_rev_(double* data, double *reservedValue, char *bytes, int *outSize, int *r1)
{
	char *tmp_bytes = SZ_compress_rev(SZ_DOUBLE, data, reservedValue, outSize, 0, 0, 0, 0, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d2_double_(double* data, char *bytes, int *outSize, int *r1, int *r2)
{
	char *tmp_bytes = SZ_compress(SZ_DOUBLE, data, outSize, 0, 0, 0, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d2_double_rev_(double* data, double *reservedValue, char *bytes, int *outSize, int *r1, int *r2)
{
	char *tmp_bytes = SZ_compress_rev(SZ_DOUBLE, data, reservedValue, outSize, 0, 0, 0, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d3_double_(double* data, char *bytes, int *outSize, int *r1, int *r2, int *r3)
{
	char *tmp_bytes = SZ_compress(SZ_DOUBLE, data, outSize, 0, 0, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d3_double_rev_(double* data, double *reservedValue, char *bytes, int *outSize, int *r1, int *r2, int *r3)
{
	char *tmp_bytes = SZ_compress_rev(SZ_DOUBLE, data, reservedValue, outSize, 0, 0, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d4_double_(double* data, char *bytes, int *outSize, int *r1, int *r2, int *r3, int *r4)
{
	char *tmp_bytes = SZ_compress(SZ_DOUBLE, data, outSize, 0, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d4_double_rev_(double* data, double *reservedValue, char *bytes, int *outSize, int *r1, int *r2, int *r3, int *r4)
{
	char *tmp_bytes = SZ_compress_rev(SZ_DOUBLE, data, reservedValue, outSize, 0, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d5_double_(double* data, char *bytes, int *outSize, int *r1, int *r2, int *r3, int *r4, int *r5)
{
	char *tmp_bytes = SZ_compress(SZ_DOUBLE, data, outSize, *r5, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d5_double_rev_(double* data, double *reservedValue, char *bytes, int *outSize, int *r1, int *r2, int *r3, int *r4, int *r5)
{
	char *tmp_bytes = SZ_compress_rev(SZ_DOUBLE, data, reservedValue, outSize, *r5, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

//compress with args

void sz_compress_d1_float_args_(float* data, char *bytes, int *outSize, int *errBoundMode, float *absErrBound, float *relBoundRatio, int *r1)
{
	char *tmp_bytes = SZ_compress_args(SZ_FLOAT, data, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, 0, 0, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d2_float_args_(float* data, char *bytes, int *outSize, int *errBoundMode, float *absErrBound, float *relBoundRatio, int *r1, int *r2)
{
	char *tmp_bytes = SZ_compress_args(SZ_FLOAT, data, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, 0, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d3_float_args_(float* data, char *bytes, int *outSize, int *errBoundMode, float *absErrBound, float *relBoundRatio, int *r1, int *r2, int *r3)
{
	char *tmp_bytes = SZ_compress_args(SZ_FLOAT, data, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d4_float_args_(float* data, char *bytes, int *outSize, int *errBoundMode, float *absErrBound, float *relBoundRatio, int *r1, int *r2, int *r3, int *r4)
{
	char *tmp_bytes = SZ_compress_args(SZ_FLOAT, data, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d5_float_args_(float* data, char *bytes, int *outSize, int *errBoundMode, float *absErrBound, float *relBoundRatio, int *r1, int *r2, int *r3, int *r4, int *r5)
{
	char *tmp_bytes = SZ_compress_args(SZ_FLOAT, data, outSize, *errBoundMode, *absErrBound, *relBoundRatio, *r5, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d1_double_args_(double* data, char *bytes, int *outSize, int *errBoundMode, double *absErrBound, double *relBoundRatio, int *r1)
{
	char *tmp_bytes = SZ_compress_args(SZ_DOUBLE, data, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, 0, 0, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d2_double_args_(double* data, char *bytes, int *outSize, int *errBoundMode, double *absErrBound, double *relBoundRatio, int *r1, int *r2)
{
	char *tmp_bytes = SZ_compress_args(SZ_DOUBLE, data, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, 0, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d3_double_args_(double* data, char *bytes, int *outSize, int *errBoundMode, double *absErrBound, double *relBoundRatio, int *r1, int *r2, int *r3)
{
	char *tmp_bytes = SZ_compress_args(SZ_DOUBLE, data, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d4_double_args_(double* data, char *bytes, int *outSize, int *errBoundMode, double *absErrBound, double *relBoundRatio, int *r1, int *r2, int *r3, int *r4)
{
	char *tmp_bytes = SZ_compress_args(SZ_DOUBLE, data, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d5_double_args_(double* data, char *bytes, int *outSize, int *errBoundMode, double *absErrBound, double *relBoundRatio, int *r1, int *r2, int *r3, int *r4, int *r5)
{
	char *tmp_bytes = SZ_compress_args(SZ_DOUBLE, data, outSize, *errBoundMode, *absErrBound, *relBoundRatio, *r5, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

//--------------

void sz_compress_d1_float_rev_args_(float* data, float *reservedValue, char *bytes, int *outSize, int *errBoundMode, float *absErrBound, float *relBoundRatio, int *r1)
{
	char *tmp_bytes = SZ_compress_rev_args(SZ_FLOAT, data, reservedValue, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, 0, 0, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d2_float_rev_args_(float* data, float *reservedValue, char *bytes, int *outSize, int *errBoundMode, float *absErrBound, float *relBoundRatio, int *r1, int *r2)
{
	char *tmp_bytes = SZ_compress_rev_args(SZ_FLOAT, data, reservedValue, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, 0, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d3_float_rev_args_(float* data, float *reservedValue, char *bytes, int *outSize, int *errBoundMode, float *absErrBound, float *relBoundRatio, int *r1, int *r2, int *r3)
{
	char *tmp_bytes = SZ_compress_rev_args(SZ_FLOAT, data, reservedValue, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d4_float_rev_args_(float* data, float *reservedValue, char *bytes, int *outSize, int *errBoundMode, float *absErrBound, float *relBoundRatio, int *r1, int *r2, int *r3, int *r4)
{
	char *tmp_bytes = SZ_compress_rev_args(SZ_FLOAT, data, reservedValue, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d5_float_rev_args_(float* data, float *reservedValue, char *bytes, int *outSize, int *errBoundMode, float *absErrBound, float *relBoundRatio, int *r1, int *r2, int *r3, int *r4, int *r5)
{
	char *tmp_bytes = SZ_compress_rev_args(SZ_FLOAT, data, reservedValue, outSize, *errBoundMode, *absErrBound, *relBoundRatio, *r5, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d1_double_rev_args_(double* data, float *reservedValue, char *bytes, int *outSize, int *errBoundMode, double *absErrBound, double *relBoundRatio, int *r1)
{
	char *tmp_bytes = SZ_compress_rev_args(SZ_DOUBLE, data, reservedValue, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, 0, 0, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d2_double_rev_args_(double* data, float *reservedValue, char *bytes, int *outSize, int *errBoundMode, double *absErrBound, double *relBoundRatio, int *r1, int *r2)
{
	char *tmp_bytes = SZ_compress_rev_args(SZ_DOUBLE, data, reservedValue, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, 0, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d3_double_rev_args_(double* data, float *reservedValue, char *bytes, int *outSize, int *errBoundMode, double *absErrBound, double *relBoundRatio, int *r1, int *r2, int *r3)
{
	char *tmp_bytes = SZ_compress_rev_args(SZ_DOUBLE, data, reservedValue, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, 0, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d4_double_rev_args_(double* data, double *reservedValue, char *bytes, int *outSize, int *errBoundMode, double *absErrBound, double *relBoundRatio, int *r1, int *r2, int *r3, int *r4)
{
	char *tmp_bytes = SZ_compress_rev_args(SZ_DOUBLE, data, reservedValue, outSize, *errBoundMode, *absErrBound, *relBoundRatio, 0, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

void sz_compress_d5_double_rev_args_(double* data, double *reservedValue, char *bytes, int *outSize, int *errBoundMode, double *absErrBound, double *relBoundRatio, int *r1, int *r2, int *r3, int *r4, int *r5)
{
	char *tmp_bytes = SZ_compress_rev_args(SZ_DOUBLE, data, reservedValue, outSize, *errBoundMode, *absErrBound, *relBoundRatio, *r5, *r4, *r3, *r2, *r1);
	memcpy(bytes, tmp_bytes, *outSize);
}

//decompress

void sz_decompress_d1_float_(char *bytes, int *byteLength, float *data, int *r1)
{
	float *tmp_data = SZ_decompress(SZ_FLOAT, bytes, *byteLength, 0, 0, 0, 0, *r1);
	memcpy(data, tmp_data, (*r1)*sizeof(float));
}

void sz_decompress_d2_float_(char *bytes, int *byteLength, float *data, int *r1, int *r2)
{
	int r;
	float *tmp_data = SZ_decompress(SZ_FLOAT, bytes, *byteLength, 0, 0, 0, *r2, *r1);
	r=(*r1)*(*r2);
	memcpy(data, tmp_data, r*sizeof(float));
}

void sz_decompress_d3_float_(char *bytes, int *byteLength, float *data, int *r1, int *r2, int *r3)
{
	int r;
	float *tmp_data = SZ_decompress(SZ_FLOAT, bytes, *byteLength, 0, 0, *r3, *r2, *r1);
	r=(*r1)*(*r2)*(*r3);
	memcpy(data, tmp_data, r*sizeof(float));
}

void sz_decompress_d4_float_(char *bytes, int *byteLength, float *data, int *r1, int *r2, int *r3, int *r4)
{
	int r;
	float *tmp_data = SZ_decompress(SZ_FLOAT, bytes, *byteLength, 0, *r4, *r3, *r2, *r1);
	r=(*r1)*(*r2)*(*r3)*(*r4);
	memcpy(data, tmp_data, r*sizeof(float));
}

void sz_decompress_d5_float_(char *bytes, int *byteLength, float *data, int *r1, int *r2, int *r3, int *r4, int *r5)
{
	int r;
	float *tmp_data = SZ_decompress(SZ_FLOAT, bytes, *byteLength, *r5, *r4, *r3, *r2, *r1);
	r=(*r1)*(*r2)*(*r3)*(*r4)*(*r5);
	memcpy(data, tmp_data, r*sizeof(float));
}

void sz_decompress_d1_double_(char *bytes, int *byteLength, double *data, int *r1)
{
	double *tmp_data = SZ_decompress(SZ_DOUBLE, bytes, *byteLength, 0, 0, 0, 0, *r1);
	memcpy(data, tmp_data, (*r1)*sizeof(double));
}

void sz_decompress_d2_double_(char *bytes, int *byteLength, double *data, int *r1, int *r2)
{
	int r;
	double *tmp_data = SZ_decompress(SZ_DOUBLE, bytes, *byteLength, 0, 0, 0, *r2, *r1);
	r=(*r1)*(*r2);
	memcpy(data, tmp_data, r*sizeof(double));
}

void sz_decompress_d3_double_(char *bytes, int *byteLength, double *data, int *r1, int *r2, int *r3)
{
	int r;
	double *tmp_data = SZ_decompress(SZ_DOUBLE, bytes, *byteLength, 0, 0, *r3, *r2, *r1);
	r=(*r1)*(*r2)*(*r3);
	memcpy(data, tmp_data, r*sizeof(double));
}

void sz_decompress_d4_double_(char *bytes, int *byteLength, double *data, int *r1, int *r2, int *r3, int *r4)
{
	int r;
	double *tmp_data = SZ_decompress(SZ_DOUBLE, bytes, *byteLength, 0, *r4, *r3, *r2, *r1);
	r=(*r1)*(*r2)*(*r3)*(*r4);
	memcpy(data, tmp_data, r*sizeof(double));
}

void sz_decompress_d5_double_(char *bytes, int *byteLength, double *data, int *r1, int *r2, int *r3, int *r4, int *r5)
{
	int r;
	double *tmp_data = SZ_decompress(SZ_DOUBLE, bytes, *byteLength, *r5, *r4, *r3, *r2, *r1);
	r=(*r1)*(*r2)*(*r3)*(*r4)*(*r5);
	memcpy(data, tmp_data, r*sizeof(double));
}

