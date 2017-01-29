/**
 *  @file io.h
 *  @author Sheng Di
 *  @date April, 2015
 *  @brief Header file for the whole io interface.
 *  (C) 2015 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#ifndef _IO_H
#define _IO_H

#include <stdio.h>
#include <stdio.h>

#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

int checkFileSize(char *srcFilePath);
char * readByteData(char *srcFilePath, int *byteLength);
double * readDoubleData(char *srcFilePath, int *nbEle);
float * readFloatData(char *srcFilePath, int *nbEle);
void writeByteData(char *bytes, int outSize, char *tgtFilePath);
void writeDoubleData(double *data, int nbEle, char *tgtFilePath);
void writeFloatData(float *data, int nbEle, char *tgtFilePath);

#endif /* ----- #ifndef _IO_H  ----- */
