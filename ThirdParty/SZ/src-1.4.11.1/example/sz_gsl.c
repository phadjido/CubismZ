#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_wavelet.h>
#include "sz.h"
#include "rw.h"

struct timeval startTime;
struct timeval endTime;  /* Start and end times */
struct timeval costStart; /*only used for recording the cost*/
double totalCost = 0;

void cost_start()
{
	totalCost = 0;
	gettimeofday(&costStart, NULL);
}

void cost_end()
{
	double elapsed;
	struct timeval costEnd;
	gettimeofday(&costEnd, NULL);
	elapsed = ((costEnd.tv_sec*1000000+costEnd.tv_usec)-(costStart.tv_sec*1000000+costStart.tv_usec))/1000000.0;
	totalCost += elapsed;
}


void usage()
{
	printf("Usage: sz <options>\n");
	printf("Options:\n");
	printf("* operation type:\n");
	printf("	-z: compression\n");
	printf("	-x: decompression\n");
	printf("* data type:\n");
	printf("	-f: single precision (float type)\n");
	printf("	-d: double precision (double type)\n");
	printf("* configuration file: \n");
	printf("	-c <configuration file> : configuration file sz.config\n");	
	printf("* input data file:\n");
	printf("	-i <original data file> : original data file\n");
	printf("	-s <compressed data file> : compressed data file in decompression\n");
	printf("* output type of decompressed file: \n");
	printf("	-b (by default) : decompressed file stored in binary format\n");
	printf("	-t : decompreadded file stored in text format\n");
	printf("	-W : pre-processing with wavelets transformation\n");
	printf("	-T : pre-processing with Tucker Tensor Decomposition\n");
	printf("* dimensions: \n");
	printf("	-1 <nx> : dimension for 1D data such as data[nx]\n");
	printf("	-2 <nx> <ny> : dimensions for 2D data such as data[ny][nx]\n");
	printf("	-3 <nx> <ny> <nz> : dimensions for 3D data such as data[nz][ny][nx] \n");
	printf("	-4 <nx> <ny> <nz> <np>: dimensions for 4D data such as data[np][nz][ny][nx] \n");
	printf("* print compression results: \n");
	printf("	-a : print compression results such as distortions\n");
	printf("* examples: \n");
	printf("	sz -z -f -c sz.config -i testdata/x86/testfloat_8_8_128.dat -3 8 8 128\n");
	printf("	sz -x -f -s testdata/x86/testfloat_8_8_128.dat.sz -3 8 8 128\n");
	printf("	sz -x -f -s testdata/x86/testfloat_8_8_128.dat.sz -i testdata/x86/testfloat_8_8_128.dat -3 8 8 128 -a\n");	
	printf("	sz -z -d -c sz.config -i testdata/x86/testdouble_8_8_128.dat -3 8 8 128\n");
	printf("	sz -x -d -s testdata/x86/testdouble_8_8_128.dat.sz -3 8 8 128\n");
	exit(0);
}


int main(int argc, char* argv[])
{
	int binaryOutput = 1;
	int printCmpResults = 0;
	int isCompression = 0; //1 : compression ; 0: decompression
	int dataType = 0; //0: single precision ; 1: double precision
	int wavelets = 0; //0: without wavelets preprocessing; 1: with wavelets preprocessing
	int tucker = 0; //0: without tucker tensor decomposition preprocessing; 1: with tucker tensor decomposition
	char* inPath = NULL;
	char* cmpPath = NULL;
	char* conPath = NULL;
	
	size_t r5 = 0;
	size_t r4 = 0;
	size_t r3 = 0;
	size_t r2 = 0; 
	size_t r1 = 0;
	
	size_t n  = 0;
	
	size_t i = 0;
	int status;
	size_t nbEle;
	if(argc==1)
		usage();
	
	for(i=1;i<argc;i++)
	{
		if (argv[i][0] != '-' || argv[i][2])
			usage();
		switch (argv[i][1])
		{
		case 'b': 
			binaryOutput = 1;
			break;
		case 't': 
			binaryOutput = 0;
			break;
		case 'a':
			printCmpResults = 1;
			break;
		case 'z':
			isCompression = 1;
			break;
		case 'x': 
			isCompression = 0;
			break;
		case 'f': 
			dataType = 0;
			break;
		case 'd':
			dataType = 1;
			break;
		case 'i':
			if (++i == argc)
				usage();
			inPath = argv[i];		
			break;
		case 's':
			if (++i == argc)
				usage();
			cmpPath = argv[i];
			break;
		case 'c':
			if (++i == argc)
				usage();
			conPath = argv[i];
			break;
		case 'W':
			wavelets = 1;
			break;
		case 'T':
			tucker = 1;
			break;
		case '1': 
			if (++i == argc || sscanf(argv[i], "%zu", &r1) != 1)
				usage();

			break;
		case '2':
			if (++i == argc || sscanf(argv[i], "%zu", &r1) != 1 ||
				++i == argc || sscanf(argv[i], "%zu", &r2) != 1)
				usage();
			break;
		case '3':
			if (++i == argc || sscanf(argv[i], "%zu", &r1) != 1 ||
				++i == argc || sscanf(argv[i], "%zu", &r2) != 1 ||
				++i == argc || sscanf(argv[i], "%zu", &r3) != 1)
				usage();		
			break;
		case '4':
			if (++i == argc || sscanf(argv[i], "%zu", &r1) != 1 ||
				++i == argc || sscanf(argv[i], "%zu", &r2) != 1 ||
				++i == argc || sscanf(argv[i], "%zu", &r3) != 1 ||
				++i == argc || sscanf(argv[i], "%zu", &r4) != 1)
				usage();		
			break;
		default: 
			usage();
			break;
		}
	}

	if ((r1==0) && (r2==0) && (r3==0) && (r4==0) && (r5==0))
	{
		printf ("Error: please specify dimensions.\n");
		printf("-1 <nx> : dimension for 1D data such as data[nx]\n");
		printf("-2 <nx> <ny> : dimensions for 2D data such as data[ny][nx]\n");
		printf("-3 <nx> <ny> <nz> : dimensions for 3D data such as data[nz][ny][nx] \n");
		printf("-4 <nx> <ny> <nz> <np>: dimensions for 4D data such as data[np][nz][ny][nx] \n");
		exit(0);
	}

	if(isCompression == 1)
	{
		if(conPath==NULL)
		{
			printf("Error: compression requires configuration file sz.config\n");
			printf("Please add -c sz.config in the command\n");
			exit(0); 
		}

		size_t outSize;
		char outputFilePath[256];		
		SZ_Init(conPath);
		if(dataType == 0) //single precision
		{
			if(tucker)
			{
				printf("Error: Single-precision Tucker tensor decomposition is not supported by TuckerMPI yet. \n");
				printf("Solution: change the data format to be double-precision and then do the tensor decomposition.\n");
				exit(0);
			}

			float *data = readFloatData(inPath, &nbEle, &status);

			if (wavelets)
			{			
				n = nbEle - 1; n |= n >> 1; n |= n >> 2; n |= n >> 4;
				n |= n >> 8; n |= n >> 16; n++;

				double *dwtdata = malloc(n * sizeof (double));
				gsl_wavelet *w;
				gsl_wavelet_workspace *work;

				w = gsl_wavelet_alloc (gsl_wavelet_daubechies, 4);
				work = gsl_wavelet_workspace_alloc (n);

				for (i = 0; i < nbEle; i++)
				  dwtdata[i] = (double)data[i];
				memset(dwtdata+r1, 0, sizeof(double)*(n-nbEle));

				status = gsl_wavelet_transform_forward (w, dwtdata, 1, n, work);

				if (status != GSL_SUCCESS)
				{
					printf ("Error: wavelets transform failed.\n");
					exit(0);
				}

				for (i = 0; i < r1; i++)
				  data[i] = (float)dwtdata[i];

				gsl_wavelet_free (w);
				gsl_wavelet_workspace_free (work);

				free (dwtdata);
			}
			cost_start();	
			unsigned char *bytes = SZ_compress(SZ_FLOAT, data, &outSize, r5, r4, r3, r2, r1);
			cost_end();
			sprintf(outputFilePath, "%s.sz", inPath);
			writeByteData(bytes, outSize, outputFilePath, &status);		
			free(data);
			free(bytes);
			if(status != SZ_SCES)
			{
				printf("Error: data file %s cannot be written!\n", outputFilePath);
				exit(0);
			}
			printf("compression time = %f\n", totalCost);
			printf("compressed data file: %s\n", outputFilePath);			
		}
		else //dataType == 1: double precision
		{
			if(tucker)
			{
				const char* s = getenv("TUCKERMPI_PATH");
				if(s==NULL)
				{
					printf("Error: the environment variable TUCKERMPI_PATH == NULL. \n");
					printf("Solution: Install TuckerMPI and set environment variable TUCKERMPI_HOME to the building path (e.g., TuckerMPI-gitlab/build)\n"); 
					exit(0);
				}	
				
				//TODO: constructing the parameter-raw.txt	
				char *str[8] = {
					"Automatic rank determination = true", 
					"Perform STHOSVD = true", 
					"Write STHOSVD result = true", 
					"Print options = true", 
					NULL, 
					"Scaling type = StandardCentering", 
					"Scale mode = 2", 
					NULL};
							
				char dimStr[256];
				if(r2==0)
					sprintf(dimStr, "Global dims = %zu", r1);
				else if(r3==0)
					sprintf(dimStr, "Global dims = %zu %zu", r2, r1);
				else if(r4==0)
					sprintf(dimStr, "Global dims = %zu %zu %zu", r3, r2, r1);
				else if(r5==0)
					sprintf(dimStr, "Global dims = %zu %zu %zu %zu", r4, r3, r2, r1);
				else
					sprintf(dimStr, "Global dims = %zu %zu %zu %zu %zu", r5, r4, r3, r2, r1);
				
				str[4] = dimStr;
				
				char thrStr[100]; 
				sprintf(thrStr, "SV Threshold = %f", absErrBound);
				str[7] = thrStr;

				writeStrings(8, str, "parameter-raw.txt", &status);	

				//TODO: constructing the raw.txt (containing the path of the binary data file
				char* dataPathStr[1];
				dataPathStr[0] = inPath;
				writeStrings(1, dataPathStr, "raw.txt", &status);
				
				printf("calling TuckerMPI interface to do the Tucker Tensor Decomposition....\n");
				
				system("mkdir -p ./compressed");
				system("${TUCKERMPI_PATH}/serial/drivers/bin/Tucker_sthosvd --parameter-file parameter-raw.txt");
			}
			else
			{
				double *data = readDoubleData(inPath, &nbEle, &status);	
				if (wavelets)
				{
					n = nbEle - 1; n |= n >> 1; n |= n >> 2; n |= n >> 4;
					n |= n >> 8; n |= n >> 16; n++;
					
					double *dwtdata = malloc(n * sizeof (double));
					gsl_wavelet *w;
					gsl_wavelet_workspace *work;

					w = gsl_wavelet_alloc (gsl_wavelet_daubechies, 4);
					work = gsl_wavelet_workspace_alloc (n);

					memcpy(dwtdata, data, sizeof(double)*nbEle);
					memset(dwtdata+nbEle, 0, sizeof(double)*(n-nbEle));

					status = gsl_wavelet_transform_forward (w, dwtdata, 1, n, work);

					if (status != GSL_SUCCESS)
					{
						printf ("Error: wavelets transform failed.\n");
						exit(0);
					}

					memcpy(data, dwtdata, sizeof(double)*nbEle);

					gsl_wavelet_free (w);
					gsl_wavelet_workspace_free (work);

					free (dwtdata);
				}
				cost_start();
				unsigned char *bytes = SZ_compress(SZ_DOUBLE, data, &outSize, r5, r4, r3, r2, r1);
				cost_end();
				sprintf(outputFilePath, "%s.sz", inPath);
				writeByteData(bytes, outSize, outputFilePath, &status);		
				free(data);
				free(bytes);
				if(status != SZ_SCES)
				{
					printf("Error: data file %s cannot be written!\n", outputFilePath);
					exit(0);
				}		
				printf("compression time = %f\n", totalCost);
				printf("compressed data file: %s\n", outputFilePath);
			}	
		}

		if (printCmpResults == 1)
		{
			printf ("Error: -a can be only used in decompression.\n");
		}
	}
	else //decompression
	{
		if(printCmpResults)
		{
			if(inPath==NULL)
			{
				printf("Error: Since you add -a option (analysis), please specify the original data path by -i <path>.\n");
				exit(0);
			}
		}		
		
		size_t byteLength;
		char outputFilePath[256];

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

		if(dataType == 0)
		{
			if(tucker)
			{
				printf("Error: Single-precision Tucker tensor decomposition is not supported by TuckerMPI yet. \n");
				printf("Solution: change the data format to be double-precision and then do the tensor decomposition.\n");
				exit(0);
			}			
			
			unsigned char *bytes = readByteData(cmpPath, &byteLength, &status);
			if(status!=SZ_SCES)
			{
				printf("Error: %s cannot be read!\n", cmpPath);
				exit(0);
			}
			cost_start();
			float *data = SZ_decompress(SZ_FLOAT, bytes, byteLength, r5, r4, r3, r2, r1);			
			cost_end();
			free(bytes);


			if (wavelets)
			{
				n = nbEle - 1; n |= n >> 1; n |= n >> 2; n |= n >> 4;
				n |= n >> 8; n |= n >> 16; n++;

				double *dwtdata = malloc(n * sizeof (double));
				gsl_wavelet *w;
				gsl_wavelet_workspace *work;

				w = gsl_wavelet_alloc (gsl_wavelet_daubechies, 4);
				work = gsl_wavelet_workspace_alloc (n);

				for (i = 0; i < nbEle; i++)
				  dwtdata[i] = (double)data[i];
				memset(dwtdata+r1, 0, sizeof(double)*(n-nbEle));

				status = gsl_wavelet_transform_inverse (w, dwtdata, 1, n, work);

				if (status != GSL_SUCCESS)
				{
					printf ("Error: wavelets transform failed.\n");
					exit(0);
				}

				for (i = 0; i < nbEle; i++)
				  data[i] = (float)dwtdata[i];

				gsl_wavelet_free (w);
				gsl_wavelet_workspace_free (work);

				free (dwtdata);
			}
			sprintf(outputFilePath, "%s.out", cmpPath);	
			if(binaryOutput==1)		
			  writeFloatData_inBytes(data, nbEle, outputFilePath, &status);
			else //txt output
			  writeFloatData(data, nbEle, outputFilePath, &status);

			if(status!=SZ_SCES)
			{
				printf("Error: %s cannot be written!\n", outputFilePath);
				exit(0);
			}

			if(printCmpResults)
			{
				if(inPath==NULL)
				{
					printf("Error: Since you add -a option (analysis), please specify the original data path by -i <path>.\n");
					exit(0);
				}
				//compute the distortion / compression errors...
				size_t totalNbEle;
				float *ori_data = readFloatData(inPath, &totalNbEle, &status);
				if(status!=SZ_SCES)
				{
					printf("Error: %s cannot be read!\n", inPath);
					exit(0);
				}

				size_t i = 0;
				float Max = 0, Min = 0, diffMax = 0;
				Max = ori_data[0];
				Min = ori_data[0];
				diffMax = fabs(data[0] - ori_data[0]);
				size_t k = 0;
				double sum1 = 0, sum2 = 0;
				for (i = 0; i < nbEle; i++)
				{
					sum1 += ori_data[i];
					sum2 += data[i];
				}
				double mean1 = sum1/nbEle;
				double mean2 = sum2/nbEle;

				double sum3 = 0, sum4 = 0;
				double sum = 0, prodSum = 0, relerr = 0;

				double maxpw_relerr = 0; 
				for (i = 0; i < nbEle; i++)
				{
					if (Max < ori_data[i]) Max = ori_data[i];
					if (Min > ori_data[i]) Min = ori_data[i];

					float err = fabs(data[i] - ori_data[i]);
					if(ori_data[i]!=0)
					{
						relerr = err/ori_data[i];
						if(maxpw_relerr<relerr)
						  maxpw_relerr = relerr;
					}

					if (diffMax < err)
					  diffMax = err;
					prodSum += (ori_data[i]-mean1)*(data[i]-mean2);
					sum3 += (ori_data[i] - mean1)*(ori_data[i]-mean1);
					sum4 += (data[i] - mean2)*(data[i]-mean2);
					sum += err*err;	
				}
				double std1 = sqrt(sum3/nbEle);
				double std2 = sqrt(sum4/nbEle);
				double ee = prodSum/nbEle;
				double acEff = ee/std1/std2;

				double mse = sum/nbEle;
				double range = Max - Min;
				double psnr = 20*log10(range)-10*log10(mse);
				double nrmse = sqrt(mse)/range;

				printf ("Min=%.20G, Max=%.20G, range=%.20G\n", Min, Max, range);
				printf ("Max absolute error = %.10f\n", diffMax);
				printf ("Max relative error = %f\n", diffMax/(Max-Min));
				printf ("Max pw relative error = %f\n", maxpw_relerr);
				printf ("PSNR = %f, NRMSE= %.20G\n", psnr,nrmse);
				printf ("acEff=%f\n", acEff);	
			}
			free(data);	
			
			printf("decompression time = %f seconds.\n", totalCost);
			printf("decompressed data file: %s\n", outputFilePath);							
		}
		else //double-data
		{
			double *data;
			if(tucker)
			{
				const char* s = getenv("TUCKERMPI_PATH");
				if(s==NULL)
				{
					printf("Error: the environment variable TUCKERMPI_PATH == NULL. \n");
					printf("Solution: Install TuckerMPI and set environment variable TUCKERMPI_HOME to the building path (e.g., TuckerMPI-gitlab/build)\n"); 
					exit(0);
				}	
				
				//TODO: constructing the parameter-raw.txt	
				char *str[4] = {
					"Print options = true", 
					NULL, 
					NULL, 
					"STHOSVD directory = ./compressed"};
				char dimStr1[256];
				if(r2==0)
					sprintf(dimStr1, "Beginning subscripts = 0");
				else if(r3==0)
					sprintf(dimStr1, "Beginning subscripts = 0 0");
				else if(r4==0)
					sprintf(dimStr1, "Beginning subscripts = 0 0 0");
				else if(r5==0)
					sprintf(dimStr1, "Beginning subscripts = 0 0 0 0");
				else
					sprintf(dimStr1, "Beginning subscripts = 0 0 0 0 0");
				
				str[1] = dimStr1;
						
				char dimStr2[256];
				if(r2==0)
					sprintf(dimStr2, "Ending subscripts = %zu", r1-1);
				else if(r3==0)
					sprintf(dimStr2, "Ending subscripts = %zu %zu", r2-1, r1-1);
				else if(r4==0)
					sprintf(dimStr2, "Ending subscripts = %zu %zu %zu", r3-1, r2-1, r1-1);
				else if(r5==0)
					sprintf(dimStr2, "Ending subscripts = %zu %zu %zu %zu", r4-1, r3-1, r2-1, r1-1);
				else
					sprintf(dimStr2, "Ending subscripts = %zu %zu %zu %zu %zu", r5-1, r4-1, r3-1, r2-1, r1-1);
				
				str[2] = dimStr2;

				writeStrings(4, str, "parameter-rec.txt", &status);		

				//TODO: constructing the raw.txt (containing the path of the binary data file				
				strcpy(outputFilePath, "tucker-decompress.out");
				char* dataPathStr[1];
				dataPathStr[0] = outputFilePath;
				writeStrings(1, dataPathStr, "rec.txt", &status);
				
				printf("calling TuckerMPI interface to do the Tucker Tensor Decomposition....\n");
				
				system("${TUCKERMPI_PATH}/serial/drivers/bin/Tucker_reconstruct --parameter-file parameter-rec.txt");
			}
			else
			{
				unsigned char *bytes = readByteData(cmpPath, &byteLength, &status);
				if(status!=SZ_SCES)
				{
					printf("Error: %s cannot be read!\n", cmpPath);
					exit(0);
				}
				cost_start();
				data = SZ_decompress(SZ_DOUBLE, bytes, byteLength, r5, r4, r3, r2, r1);			
				cost_end();
				free(bytes);
				if (wavelets)
				{	
					n = nbEle - 1; n |= n >> 1; n |= n >> 2; n |= n >> 4;
					n |= n >> 8; n |= n >> 16; n++;

					double *dwtdata = malloc(n * sizeof (double));
					gsl_wavelet *w;
					gsl_wavelet_workspace *work;

					w = gsl_wavelet_alloc (gsl_wavelet_daubechies, 4);
					work = gsl_wavelet_workspace_alloc (n);

					memcpy(dwtdata, data, sizeof(double)*nbEle);
					memset(dwtdata+nbEle, 0, sizeof(double)*(n-nbEle));

					status = gsl_wavelet_transform_inverse (w, dwtdata, 1, n, work);

					memcpy(data, dwtdata, sizeof(double)*nbEle);

					gsl_wavelet_free (w);
					gsl_wavelet_workspace_free (work);

					free (dwtdata);
				}
				sprintf(outputFilePath, "%s.out", cmpPath);
				if(binaryOutput==1)		
				  writeDoubleData_inBytes(data, nbEle, outputFilePath, &status);
				else //txt output
				  writeDoubleData(data, nbEle, outputFilePath, &status);			
				if(status!=SZ_SCES)
				{
					printf("Error: %s cannot be written!\n", outputFilePath);
					exit(0);
				}
						
				printf("decompression time = %f seconds.\n", totalCost);
				printf("decompressed data file: %s\n", outputFilePath);										
			}
			
			if(printCmpResults)
			{
				size_t totalNbEle;

				if(tucker)
					data = readDoubleData("tucker-decompress.out", &totalNbEle, &status);

				//compute the distortion / compression errors...
				double *ori_data = readDoubleData(inPath, &totalNbEle, &status);
				if(status!=SZ_SCES)
				{
					printf("Error: %s cannot be read!\n", inPath);
					exit(0);
				}

				size_t i = 0;
				double Max = 0, Min = 0, diffMax = 0;
				Max = ori_data[0];
				Min = ori_data[0];
				diffMax = data[0]>ori_data[0]?data[0]-ori_data[0]:ori_data[0]-data[0];

				//diffMax = fabs(data[0] - ori_data[0]);
				size_t k = 0;
				double sum1 = 0, sum2 = 0;

				for (i = 0; i < nbEle; i++)
				{
					sum1 += ori_data[i];
					sum2 += data[i];
				}
				double mean1 = sum1/nbEle;
				double mean2 = sum2/nbEle;

				double sum3 = 0, sum4 = 0;
				double sum = 0, prodSum = 0, relerr = 0;

				double maxpw_relerr = 0; 
				for (i = 0; i < nbEle; i++)
				{
					if (Max < ori_data[i]) Max = ori_data[i];
					if (Min > ori_data[i]) Min = ori_data[i];

					float err = fabs(data[i] - ori_data[i]);
					if(ori_data[i]!=0)
					{
						relerr = err/ori_data[i];
						if(maxpw_relerr<relerr)
						  maxpw_relerr = relerr;
					}

					if (diffMax < err)
					  diffMax = err;
					prodSum += (ori_data[i]-mean1)*(data[i]-mean2);
					sum3 += (ori_data[i] - mean1)*(ori_data[i]-mean1);
					sum4 += (data[i] - mean2)*(data[i]-mean2);
					sum += err*err;	
				}
				double std1 = sqrt(sum3/nbEle);
				double std2 = sqrt(sum4/nbEle);
				double ee = prodSum/nbEle;
				double acEff = ee/std1/std2;

				double mse = sum/nbEle;
				double range = Max - Min;
				double psnr = 20*log10(range)-10*log10(mse);
				double nrmse = sqrt(mse)/range;

				printf ("Min=%.20G, Max=%.20G, range=%.20G\n", Min, Max, range);
				printf ("Max absolute error = %.10f\n", diffMax);
				printf ("Max relative error = %f\n", diffMax/(Max-Min));
				printf ("Max pw relative error = %f\n", maxpw_relerr);
				printf ("PSNR = %f, NRMSE= %.20G\n", psnr,nrmse);
				printf ("acEff=%f\n", acEff);
			}			
			free(data);								
		}	
	}
}
