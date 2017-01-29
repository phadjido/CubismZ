/**
 *  @file sz.c
 *  @author Sheng Di
 *  @date April, 2015
 *  @brief SZ_Init, Compression and Decompression functions
 *  (C) 2015 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sz.h"

int SZ_Init(char *configFilePath)
{
	char str[512]="", str2[512]="", str3[512]="";
	sz_cfgFile = configFilePath;
	int loadFileResult = SZ_LoadConf();
	if(loadFileResult==0)
		exit(0);
    
    memset(&vm_args, 0, sizeof(vm_args));
    vm_args.version = JNI_VERSION_1_6;

	strcat(str2, "-Xmx");
	strcat(str2, maxHeap);
	options[0].optionString = str2;
	
    strcat(str, "-Djava.class.path=");
    strcat(str, SZ_CLASSPATH);
    strcat(str, "/sz.jar");
    
    strcat(str3, SZ_CLASSPATH);
    strcat(str3, "/sz.jar");
    
    if(access(str3, F_OK)!=0)
    {
		printf("Error: library file sz.jar cannot be found in %s\n", SZ_CLASSPATH);
		printf("Please check the SZ_CLASSPATH in sz.config\n");
		exit(0); 
	}
	
    options[1].optionString = str;
	
	vm_args.options = options;
    
    vm_args.nOptions = 2;
    vm_args.options = options;
     
    // Initialize java virtual machine
    status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if(status == JNI_ERR)
	{
		printf("Error: initialization of JVM is failed. \nPlease check if jdk is installed and its version is 1.6+\n");
		return 1;
	}
	else
	{
		//printf("Initialization of JVM: successful.\n");
		cls = (*env)->FindClass(env, "compression/SingleFillingCurveCompressVariable");
		mid = (*env)->GetStaticMethodID(env, cls, "initParameters", "(I)V");	
		if(mid != 0)
			(*env)->CallStaticObjectMethod(env, cls, mid, offset);
		return 0;
	}
}

int computeDataLength(int r5, int r4, int r3, int r2, int r1)
{
	int dataLength;
	if(r1==0) 
	{
		dataLength = 0;
	}
	else if(r2==0) 
	{
		dataLength = r1;
	}
	else if(r3==0) 
	{
		dataLength = r1*r2;
	}
	else if(r4==0) 
	{
		dataLength = r1*r2*r3;
	}
	else if(r5==0) 
	{
		dataLength = r1*r2*r3*r4;
	}
	else 
	{
		dataLength = r1*r2*r3*r4*r5;
	}
	return dataLength;
}

/*-------------------------------------------------------------------------*/
/**
    @brief      Perform Compression 
    @param      data           data to be compressed
    @param      outSize        the size (in bytes) after compression
    @param		r5,r4,r3,r2,r1	the sizes of each dimension (supporting only 5 dimensions at most in this version.
    @return     compressed data (in binary stream)

 **/
/*-------------------------------------------------------------------------*/
char *SZ_compress_args(int dataType, void *data, int *outSize, int errBoundMode, double absErrBound, double relBoundRatio, int r5, int r4, int r3, int r2, int r1)
{
	int dataLength;
	char *newByteData;
	dataLength = computeDataLength(r5,r4,r3,r2,r1);
	cls = (*env)->FindClass(env, "compression/SingleFillingCurveCompressVariable");
	
	if (cls != 0)
	{
		if(dataType==SZ_FLOAT)
		{
			float *float_data;
			float_data = (float *) data;
			mid = (*env)->GetStaticMethodID(env, cls, "SZ_compress", "([FIFFIIIII)[B");
			if(mid != 0)
			{
				jfloatArray arg1 = (*env)->NewFloatArray(env,dataLength);
				(*env)->SetFloatArrayRegion(env, arg1, 0, dataLength, float_data);
			
				jbyteArray result = (jbyteArray)(*env)->CallStaticObjectMethod(env, cls, mid, arg1, errBoundMode, (float)absErrBound, (float)relBoundRatio, r5, r4, r3, r2, r1);
				newByteData = (*env)->GetByteArrayElements(env, result, NULL);
				*outSize = (*env)->GetArrayLength(env, result);
				(*env)->ReleaseByteArrayElements(env, result, newByteData, JNI_COMMIT);	
				(*env)->DeleteLocalRef(env, result);
			}
		}
		else if(dataType==SZ_DOUBLE)
		{
			double *double_data;
			double_data = (double *) data;
			mid = (*env)->GetStaticMethodID(env, cls, "SZ_compress", "([DIDDIIIII)[B");
			if(mid != 0)
			{
				jdoubleArray arg1 = (*env)->NewDoubleArray(env,dataLength);
				(*env)->SetDoubleArrayRegion(env, arg1, 0, dataLength, double_data);
			
				jbyteArray result = (jbyteArray)(*env)->CallStaticObjectMethod(env, cls, mid, arg1, errBoundMode, absErrBound, relBoundRatio, r5, r4, r3, r2, r1);
				newByteData = (*env)->GetByteArrayElements(env, result, NULL);
				*outSize = (*env)->GetArrayLength(env, result);
				(*env)->ReleaseByteArrayElements(env, result, newByteData, JNI_COMMIT);		
				(*env)->DeleteLocalRef(env, result);	
			}				
		}
		else
		{
			printf("Error: data type cannot be the types other than SZ_FLOAT or SZ_DOUBLE\n");
			exit(0);
		}


		return newByteData;	
	}	
}

int SZ_compress_args2(int dataType, void *data, char* compressed_bytes, int *outSize, int errBoundMode, double absErrBound, double relBoundRatio, int r5, int r4, int r3, int r2, int r1)
{
	char* bytes = SZ_compress_args(dataType, data, outSize, errBoundMode, absErrBound, relBoundRatio, r5, r4, r3, r2, r1);
	memcpy(compressed_bytes, bytes, *outSize);
	//free(bytes); //free(bytes) is removed , because of dump error at MIRA system (PPC architecture)
	return 0;
}

char *SZ_compress(int dataType, void *data, int *outSize, int r5, int r4, int r3, int r2, int r1)
{
	int dataLength;

	char *newByteData;
	dataLength = computeDataLength(r5,r4,r3,r2,r1);	
	cls = (*env)->FindClass(env, "compression/SingleFillingCurveCompressVariable");	
	if (cls != 0)
	{
		if(dataType==SZ_FLOAT)
		{
			float *float_data;
			float_data = (float *)data;
			mid = (*env)->GetStaticMethodID(env, cls, "SZ_compress", "([FIFFIIIII)[B");
			if(mid != 0)
			{	
				jfloatArray arg1 = (*env)->NewFloatArray(env,dataLength);
				(*env)->SetFloatArrayRegion(env, arg1, 0, dataLength, float_data);
			
				jbyteArray result = (jbyteArray)(*env)->CallStaticObjectMethod(env, cls, mid, arg1, errorBoundMode, absErrBound, relBoundRatio, r5, r4, r3, r2, r1);
				newByteData = (*env)->GetByteArrayElements(env, result, NULL);
				*outSize = (*env)->GetArrayLength(env, result);
				(*env)->ReleaseByteArrayElements(env, result, newByteData, JNI_COMMIT);	
				(*env)->DeleteLocalRef(env, result);					
			}
		}
		else if(dataType==SZ_DOUBLE)
		{
			double *double_data;
			double_data = (double *) data;
			mid = (*env)->GetStaticMethodID(env, cls, "SZ_compress", "([DIDDIIIII)[B");
			if(mid != 0)
			{	
				jdoubleArray arg1 = (*env)->NewDoubleArray(env,dataLength);
				(*env)->SetDoubleArrayRegion(env, arg1, 0, dataLength, double_data);
			
				jbyteArray result = (jbyteArray)(*env)->CallStaticObjectMethod(env, cls, mid, arg1, errorBoundMode, absErrBound, relBoundRatio, r5, r4, r3, r2, r1);
				newByteData = (*env)->GetByteArrayElements(env, result, NULL);
				*outSize = (*env)->GetArrayLength(env, result);
				(*env)->ReleaseByteArrayElements(env, result, newByteData, JNI_COMMIT);		
				(*env)->DeleteLocalRef(env, result);				
			}
		}
		else
		{
			printf("Error: data type cannot be the types other than SZ_FLOAT or SZ_DOUBLE\n");
			exit(0);
		}
		
	}
	
	return newByteData;
}

//////////////////
/*-------------------------------------------------------------------------*/
/**
    @brief      Perform Compression 
    @param      data           data to be compressed
    @param		reservedValue  the reserved value
    @param      outSize        the size (in bytes) after compression
    @param		r5,r4,r3,r2,r1	the sizes of each dimension (supporting only 5 dimensions at most in this version.
    @return     compressed data (in binary stream)

 **/
/*-------------------------------------------------------------------------*/
char *SZ_compress_rev_args(int dataType, void *data, void *reservedValue, int *outSize, int errBoundMode, double absErrBound, double relBoundRatio, int r5, int r4, int r3, int r2, int r1)
{
	int dataLength;
	char *newByteData;
	dataLength = computeDataLength(r5,r4,r3,r2,r1);
	cls = (*env)->FindClass(env, "compression/SingleFillingCurveCompressVariable");
	
	if (cls != 0)
	{
		if(dataType==SZ_FLOAT)
		{
			float *float_revValue = (float *)reservedValue;
			float *float_data;
			float_data = (float *) data;
			mid = (*env)->GetStaticMethodID(env, cls, "SZ_compress", "([FFIFFIIIII)[B");
			if(mid != 0)
			{
				jfloatArray arg1 = (*env)->NewFloatArray(env,dataLength);
				(*env)->SetFloatArrayRegion(env, arg1, 0, dataLength, float_data);
			
				jbyteArray result = (jbyteArray)(*env)->CallStaticObjectMethod(env, cls, mid, arg1, *float_revValue, errBoundMode, (float)absErrBound, (float)relBoundRatio, r5, r4, r3, r2, r1);
				newByteData = (*env)->GetByteArrayElements(env, result, NULL);
				*outSize = (*env)->GetArrayLength(env, result);
				(*env)->ReleaseByteArrayElements(env, result, newByteData, JNI_COMMIT);	
				(*env)->DeleteLocalRef(env, result);
			}
		}
		else if(dataType==SZ_DOUBLE)
		{
			double *double_revValue = (double *)reservedValue;
			double *double_data;
			double_data = (double *) data;
			mid = (*env)->GetStaticMethodID(env, cls, "SZ_compress", "([DDIDDIIIII)[B");
			if(mid != 0)
			{
				jdoubleArray arg1 = (*env)->NewDoubleArray(env,dataLength);
				(*env)->SetDoubleArrayRegion(env, arg1, 0, dataLength, double_data);
			
				jbyteArray result = (jbyteArray)(*env)->CallStaticObjectMethod(env, cls, mid, arg1, *double_revValue, errBoundMode, absErrBound, relBoundRatio, r5, r4, r3, r2, r1);
				newByteData = (*env)->GetByteArrayElements(env, result, NULL);
				*outSize = (*env)->GetArrayLength(env, result);
				(*env)->ReleaseByteArrayElements(env, result, newByteData, JNI_COMMIT);		
				(*env)->DeleteLocalRef(env, result);		
			}				
		}
		else
		{
			printf("Error: data type cannot be the types other than SZ_FLOAT or SZ_DOUBLE\n");
			exit(0);
		}

		return newByteData;	
	}	
}

int SZ_compress_rev_args2(int dataType, void *data, void *reservedValue, char* compressed_bytes, int *outSize, int errBoundMode, double absErrBound, double relBoundRatio, int r5, int r4, int r3, int r2, int r1)
{
	char* bytes = SZ_compress_rev_args(dataType, data, reservedValue, outSize, errBoundMode, absErrBound, relBoundRatio, r5, r4, r3, r2, r1);
	memcpy(compressed_bytes, bytes, *outSize);
	free(bytes); //free(bytes) is removed , because of dump error at MIRA system (PPC architecture), fixed?
	return 0;
}

char *SZ_compress_rev(int dataType, void *data, void *reservedValue, int *outSize, int r5, int r4, int r3, int r2, int r1)
{
	int dataLength;

	char *newByteData;
	dataLength = computeDataLength(r5,r4,r3,r2,r1);	
	cls = (*env)->FindClass(env, "compression/SingleFillingCurveCompressVariable");	
	if (cls != 0)
	{
		if(dataType==SZ_FLOAT)
		{
			float *float_revValue = (float *)reservedValue;
			float *float_data;
			float_data = (float *)data;
			mid = (*env)->GetStaticMethodID(env, cls, "SZ_compress", "([FFIFFIIIII)[B");
			if(mid != 0)
			{	
				jfloatArray arg1 = (*env)->NewFloatArray(env,dataLength);
				(*env)->SetFloatArrayRegion(env, arg1, 0, dataLength, float_data);
			
				jbyteArray result = (jbyteArray)(*env)->CallStaticObjectMethod(env, cls, mid, arg1, *float_revValue, errorBoundMode, absErrBound, relBoundRatio, r5, r4, r3, r2, r1);
				newByteData = (*env)->GetByteArrayElements(env, result, NULL);
				*outSize = (*env)->GetArrayLength(env, result);
				(*env)->ReleaseByteArrayElements(env, result, newByteData, JNI_COMMIT);	
				(*env)->DeleteLocalRef(env, result);					
			}
		}
		else if(dataType==SZ_DOUBLE)
		{
			double *double_revValue = (double *)reservedValue;
			double *double_data;
			double_data = (double *) data;
			mid = (*env)->GetStaticMethodID(env, cls, "SZ_compress", "([DDIDDIIIII)[B");
			if(mid != 0)
			{	
				jdoubleArray arg1 = (*env)->NewDoubleArray(env,dataLength);
				(*env)->SetDoubleArrayRegion(env, arg1, 0, dataLength, double_data);
			
				jbyteArray result = (jbyteArray)(*env)->CallStaticObjectMethod(env, cls, mid, arg1, *double_revValue, errorBoundMode, absErrBound, relBoundRatio, r5, r4, r3, r2, r1);
				newByteData = (*env)->GetByteArrayElements(env, result, NULL);
				*outSize = (*env)->GetArrayLength(env, result);
				(*env)->ReleaseByteArrayElements(env, result, newByteData, JNI_COMMIT);	
				(*env)->DeleteLocalRef(env, result);					
			}
		}
		else
		{
			printf("Error: data type cannot be the types other than SZ_FLOAT or SZ_DOUBLE\n");
			exit(0);
		}
		
	}
	
	return newByteData;
}

void *SZ_decompress(int dataType, char *bytes, int byteLength, int r5, int r4, int r3, int r2, int r1)
{
	cls = (*env)->FindClass(env, "compression/SingleFillingCurveDecompressVariable");
	if(cls != 0)
	{	
		if(dataType == SZ_FLOAT)
		{
			mid = (*env)->GetStaticMethodID(env, cls, "SZ_decompressF", "([BIIIII)[F");			
			if(mid != 0)
			{
				float *newFloatData;
				jbyteArray arg1 = (*env)->NewByteArray(env,byteLength); //even if byteLength is ulong type, it seems NewByteArray here is still with int type.
				(*env)->SetByteArrayRegion(env, arg1, 0, byteLength, bytes);
				jfloatArray result = (jfloatArray)(*env)->CallStaticObjectMethod(env, cls, mid, arg1, r5, r4, r3, r2, r1);
				newFloatData = (*env)->GetFloatArrayElements(env, result, NULL);
				(*env)->ReleaseFloatArrayElements(env, result, newFloatData, JNI_COMMIT);
				(*env)->DeleteLocalRef(env, result);
				return newFloatData;
			}
		}
		else if(dataType == SZ_DOUBLE)
		{
			mid = (*env)->GetStaticMethodID(env, cls, "SZ_decompressD", "([BIIIII)[D");
			if(mid != 0)
			{
				double *newDoubleData;
				jbyteArray arg1 = (*env)->NewByteArray(env,byteLength); //even if byteLength is ulong type, it seems NewByteArray here is still with int type.
				(*env)->SetByteArrayRegion(env, arg1, 0, byteLength, bytes);
				jdoubleArray result = (jdoubleArray)(*env)->CallStaticObjectMethod(env, cls, mid, arg1, r5, r4, r3, r2, r1);
				newDoubleData = (*env)->GetDoubleArrayElements(env, result, NULL);
				(*env)->ReleaseDoubleArrayElements(env, result, newDoubleData, JNI_COMMIT);
				(*env)->DeleteLocalRef(env, result);
				return newDoubleData;
			}
		}
		else
		{
			printf("Error: data type cannot be the types other than SZ_FLOAT or SZ_DOUBLE\n");
			exit(0);		
		}
	}
}

int SZ_decompress_args(int dataType, char *bytes, int byteLength, void* decompressed_array, int r5, int r4, int r3, int r2, int r1)
{
	int i;
	int nbEle = computeDataLength(r5,r4,r3,r2,r1);
	if(dataType == SZ_FLOAT)
	{
		float* data = (float *)SZ_decompress(dataType, bytes, byteLength, r5, r4, r3, r2, r1);
		float* data_array = (float *)decompressed_array;
		for(i=0;i<nbEle;i++)
			data_array[i] = data[i];	
		free(data); //this free operation seems to not work with BlueG/Q system.
	}
	else if(dataType == SZ_DOUBLE)
	{
		double* data = (double *)SZ_decompress(dataType, bytes, byteLength, r5, r4, r3, r2, r1);
		double* data_array = (double *)decompressed_array;
		for(i=0;i<nbEle;i++)
			data_array[i] = data[i];
		free(data); //this free operation seems to not work with BlueG/Q system.
	}
	else
	{
		printf("Error: data type cannot be the types other than SZ_FLOAT or SZ_DOUBLE\n");
		exit(0);				
	}

	return nbEle;
}

void SZ_Finalize()
{
	(*jvm)->DestroyJavaVM(jvm);
}

