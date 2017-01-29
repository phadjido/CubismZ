/**
 *  @file sz.h
 *  @author Sheng Di
 *  @date April, 2015
 *  @brief Header file for the whole detector.
 *  (C) 2015 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#ifndef _SZ_H
#define _SZ_H

#include <stdio.h>
#include <sys/time.h>      /* For gettimeofday(), in microseconds */
#include <time.h>          /* For time(), in seconds */
#include <jni.h>
#include "iniparser.h"

#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

#define SZ 101

#define ABS 0
#define REL 1
#define ABS_AND_REL 2
#define ABS_OR_REL 3

#define SZ_FLOAT 0
#define SZ_DOUBLE 1

JavaVMOption options[2];
JNIEnv *env;
JavaVM *jvm;
JavaVMInitArgs vm_args;
char maxHeap[10];
 
long status;
jclass cls;
jmethodID mid;

int sol_ID;
int errorBoundMode; //ABS, REL, ABS_AND_REL, or ABS_OR_REL

char *sz_cfgFile;
char SZ_CLASSPATH[256]; //sz.jar's path

int offset;

double absErrBound;
double relBoundRatio;

int SZ_Init(char *configFilePath);

char *SZ_compress(int dataType, void *data, int *outSize, int r5, int r4, int r3, int r2, int r1);
char *SZ_compress_args(int dataType, void *data, int *outSize, int errBoundMode, double absErrBound, double relBoundRatio, int r5, int r4, int r3, int r2, int r1);
int SZ_compress_args2(int dataType, void *data, char* compressed_bytes, int *outSize, int errBoundMode, double absErrBound, double relBoundRatio, int r5, int r4, int r3, int r2, int r1);

char *SZ_compress_rev_args(int dataType, void *data, void *reservedValue, int *outSize, int errBoundMode, double absErrBound, double relBoundRatio, int r5, int r4, int r3, int r2, int r1);
int SZ_compress_rev_args2(int dataType, void *data, void *reservedValue, char* compressed_bytes, int *outSize, int errBoundMode, double absErrBound, double relBoundRatio, int r5, int r4, int r3, int r2, int r1);
char *SZ_compress_rev(int dataType, void *data, void *reservedValue, int *outSize, int r5, int r4, int r3, int r2, int r1);

void *SZ_decompress(int dataType, char *bytes, int byteLength, int r5, int r4, int r3, int r2, int r1);
int SZ_decompress_args(int dataType, char *bytes, int byteLength, void* decompressed_array, int r5, int r4, int r3, int r2, int r1);
void SZ_Finalize();

#endif /* ----- #ifndef _SZ_H  ----- */
