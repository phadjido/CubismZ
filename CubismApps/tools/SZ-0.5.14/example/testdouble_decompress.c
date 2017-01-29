/**
 *  @file test_decompress.c
 *  @author Sheng Di
 *  @date April, 2015
 *  @brief This is an example of using Decompression interface.
 *  (C) 2015 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sz.h"
#include "rw.h"

int main(int argc, char * argv[])
{
    int r5=0,r4=0,r3,r2,r1, nbEle;
    char zipFilePath[640], outputFilePath[640];
    char *cfgFile;
    if(argc < 6)
    {
		printf("Test case: %s [configFile] [srcFilePath] [dimension sizes...]\n", argv[0]);
		printf("Example: %s sz.config testdouble_8_8_128.dat.sz 8 8 128\n", argv[0]);
		exit(0);
	}	
   
    cfgFile = argv[1];
    sprintf(zipFilePath, "%s", argv[2]);
    r1 = atoi(argv[3]); //8
    r2 = atoi(argv[4]); //8
    r3 = atoi(argv[5]); //128
    if(argc>=7)
	r4 = atoi(argv[6]);
    if(argc>=8)
        r5 = atoi(argv[7]);
    
    SZ_Init(cfgFile);
    
    nbEle = r1*r2*r3;
    if(argc>=7)
	nbEle*=r4;
    if(argc>=8)
	nbEle*=r5;
    
    sprintf(outputFilePath, "%s.out", zipFilePath);
    
    int *byteLength = (int *)malloc(sizeof(int));
    char *bytes = readByteData(zipFilePath, byteLength);
    
    double *data = SZ_decompress(SZ_DOUBLE, bytes, *byteLength, r5, r4, r3, r2, r1);
    
    writeDoubleData(data, nbEle, outputFilePath);
    
    printf("done\n");
    
    SZ_Finalize();
    
	return 0;
}
