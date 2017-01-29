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
    int r5=0,r4=0,r3=0,r2=0,r1=0, nbEle;
    char zipFilePath[640], outputFilePath[640];
    char *cfgFile;
    if(argc < 2)
    {
		printf("Test case: %s [configFile] [srcFilePath] [dimension sizes...]\n", argv[0]);
		printf("Example: %s sz.config testfloat_8_8_128.dat.sz 8 8 128\n", argv[0]);
		exit(0);
	}	
   
    cfgFile = argv[1];
    sprintf(zipFilePath, "%s", argv[2]);
    if(argc>=4)
	r1 = atoi(argv[3]); //8  
    if(argc>=5)
    	r2 = atoi(argv[4]); //8
    if(argc>=6)
    	r3 = atoi(argv[5]); //128  
    if(argc>=7)
        r4 = atoi(argv[6]);
    if(argc>=8)
        r5 = atoi(argv[7]);
    
    SZ_Init(cfgFile);
    
    if(r2==0)
	nbEle = r1;
    else if(r3==0)
	nbEle = r1*r2;
    else if(r4==0) 
    	nbEle = r1*r2*r3;
    else if(r5==0)
	nbEle = r1*r2*r3*r4;
    else
	nbEle = r1*r2*r3*r4*r5;

    sprintf(outputFilePath, "%s.out", zipFilePath);
    
    int *byteLength = (int *)malloc(sizeof(int));
    char *bytes = readByteData(zipFilePath, byteLength);
  
    //printf("r1=%d,r2=%d,r3=%d,r4=%d,r5=%d\n", r1,r2,r3,r4,r5);
 
    float *data = SZ_decompress(SZ_FLOAT, bytes, *byteLength, r5, r4, r3, r2, r1);
    //float data[r3][r2][r1];
    //nbEle = SZ_decompress_args(SZ_FLOAT, bytes, *byteLength, data, r5, r4, r3, r2, r1);
    
    //writeFloatData(data, nbEle, outputFilePath);
    
    writeData(data, SZ_FLOAT, nbEle, outputFilePath);
    printf("done\n");
    
    SZ_Finalize();
    
    return 0;
}
