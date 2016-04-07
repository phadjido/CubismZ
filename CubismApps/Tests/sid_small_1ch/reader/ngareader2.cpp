#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	char *filename = (char *)"../data/data.init";

	///////////////////////////////////////

	FILE *fid = fopen(filename,"rb");
	int dims[4];

	fread(dims, sizeof(int), 4, fid);	// read only the first 4 elements from the file

	// Dimensions
	int nx      = dims[0];
	int ny      = dims[1];
	int nz      = dims[2];
	int nvar    = dims[3];

	int nsize   = nx*ny*nz;

	//  The following lines are necessary to move the file pointer to the correct
	// location befory you start reading in the variables

	double dt, time;

	fread(&dt, sizeof(double), 1, fid);     //skipping over 'dt'
	fread(&time, sizeof(double), 1, fid);   //skipping over 'time'

	char varnames[8][nvar];

	for (int var=0; var<nvar; var++) {
		fread(varnames[var], sizeof(char), 8, fid);     //skipping over the stored names
	}

	for (int var=0; var<nvar; var++) {
		printf("var[%d] = ->%s<-\n", var, varnames[var]);
	}

	// There are usually 5 variables (or nvar number of variables) stored in the data
	// file: U, V, W, P, ZMIX. Each fread call makes the file pointer shift to the end
	// of the number of values read. Hence each subsequent fread call will start after
	// where the previous fread call stopped. Add on extra variables if necessary.

	double *dummy;
	double *U, *V, *W, *P;

	//dummy = malloc(nsize*sizeof(double));
	U = (double *)malloc(nsize*sizeof(double));
	V = (double *)malloc(nsize*sizeof(double));
	W = (double *)malloc(nsize*sizeof(double));
	P = (double *)malloc(nsize*sizeof(double));

	// dummy   = fread(fid,nsize,'real*8','ieee-le');    % will produce a column vector
	//U 	  = reshape(dummy,nx,ny,nz);% now turning the column vector into a 3D matrix

	//fread(dummy, sizeof(double), nsize, fid);
	fread(U, sizeof(double), nsize, fid);
	fread(V, sizeof(double), nsize, fid);
	fread(W, sizeof(double), nsize, fid);
	fread(P, sizeof(double), nsize, fid);
	fclose(fid);

	FILE *fu = fopen("U.bin","wb");
	FILE *fv = fopen("V.bin","wb");
	FILE *fw = fopen("W.bin","wb");
	FILE *fp = fopen("P.bin","wb");

	fwrite(U, sizeof(double), nsize, fu);
	fwrite(V, sizeof(double), nsize, fv);
	fwrite(W, sizeof(double), nsize, fw);
	fwrite(P, sizeof(double), nsize, fp);

	fclose(fu);	
	fclose(fv);	
	fclose(fw);	
	fclose(fp);	

	return 0;
}
