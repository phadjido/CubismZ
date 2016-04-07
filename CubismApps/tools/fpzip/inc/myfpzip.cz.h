#include "fpzip.h"
#include <climits>

//extern "C"
//{
static void fpz_compress4D(void *in, unsigned int inbytes, int bs, int nelem, void *out, unsigned int *outbytes, int isfloat)
{
	unsigned int dim[4] = {32, 32, 32, 1};
	int prec[4];
	int dp, i;
	int precbits = 16;

	if (bs > 0) for (i = 0; i < 3; i++) dim[i] = bs;
	dim[3] = nelem;

	if (isfloat) {
		prec[0]  = precbits;
		prec[1]  = precbits;
		prec[2]  = precbits; 
		prec[3]  = precbits;
		dp = 0;
	}
	else {
		prec[0]  = (CHAR_BIT * sizeof(double));
		prec[1]  = (CHAR_BIT * sizeof(double));
		prec[2]  = (CHAR_BIT * sizeof(double));
		prec[3]  = (CHAR_BIT * sizeof(double));
		dp = 1;
	}

	*outbytes = fpzip_memory_write(out, inbytes, in, prec, dp, dim[0], dim[1], dim[2], dim[3]);
//	*outbytes = fpzip_memory_write(out, inbytes, in, NULL, dp, dim[0], dim[1], dim[2], dim[3]);
}

static void fpz_decompress4D(char *in, unsigned int inbytes, int bs, int nelem, char *out, unsigned int *outbytes, int isfloat)
{
	unsigned int dim[4] = {32, 32, 32, 1};
	int prec[4];
	int dp, i;
	int readbytes, targetbytes;
	int precbits = 16;

	if (bs > 0) for (i = 0; i < 3; i++) dim[i] = bs;
	dim[3] = nelem;

	if (isfloat) {
		prec[0]  = precbits;
		prec[1]  = precbits;
		prec[2]  = precbits;
		prec[3]  = precbits;
		dp = 0;
		targetbytes = dim[0]*dim[1]*dim[2]*dim[3]*sizeof(float);
	}
	else {
		prec[0]  = (CHAR_BIT * sizeof(double));
		prec[1]  = (CHAR_BIT * sizeof(double));
		prec[2]  = (CHAR_BIT * sizeof(double));
		prec[3]  = (CHAR_BIT * sizeof(double));
		dp = 1;
		targetbytes = dim[0]*dim[1]*dim[2]*dim[3]*sizeof(double);
	}

	readbytes = fpzip_memory_read(in, out, prec, dp, dim[0], dim[1], dim[2], dim[3]);
//	readbytes = fpzip_memory_read(in, out, NULL, dp, dim[0], dim[1], dim[2], dim[3]);
	if (readbytes == inbytes)
		*outbytes = targetbytes;
	else
		*outbytes = -1;
}

static void fpz_compress3D(void *in, unsigned int inbytes, int bs, void *out, unsigned int *outbytes, int isfloat)
{
	unsigned int dim[4] = {32, 32, 32, 1};
	int prec[4];
	int dp, i;
	int precbits = 16;

	if (bs > 0) for (i = 0; i < 3; i++) dim[i] = bs;

	if (isfloat) {
		prec[0]  = precbits;
		prec[1]  = precbits;
		prec[2]  = precbits; 
		prec[3]  = precbits;
		dp = 0;
	}
	else {
		prec[0]  = (CHAR_BIT * sizeof(double));
		prec[1]  = (CHAR_BIT * sizeof(double));
		prec[2]  = (CHAR_BIT * sizeof(double));
		prec[3]  = (CHAR_BIT * sizeof(double));
		dp = 1;
	}

	*outbytes = fpzip_memory_write(out, inbytes, in, prec, dp, dim[0], dim[1], dim[2], dim[3]);
//	*outbytes = fpzip_memory_write(out, inbytes, in, NULL, dp, dim[0], dim[1], dim[2], dim[3]);
}

static void fpz_decompress3D(char *in, unsigned int inbytes, int bs, char *out, unsigned int *outbytes, int isfloat)
{
	unsigned int dim[4] = {32, 32, 32, 1};
	int prec[4];
	int dp, i;
	int readbytes, targetbytes;
	int precbits = 16;

	if (bs > 0) for (i = 0; i < 3; i++) dim[i] = bs;

	if (isfloat) {
		prec[0]  = precbits;
		prec[1]  = precbits;
		prec[2]  = precbits;
		prec[3]  = precbits;
		dp = 0;
		targetbytes = dim[0]*dim[1]*dim[2]*dim[3]*sizeof(float);
	}
	else {
		prec[0]  = (CHAR_BIT * sizeof(double));
		prec[1]  = (CHAR_BIT * sizeof(double));
		prec[2]  = (CHAR_BIT * sizeof(double));
		prec[3]  = (CHAR_BIT * sizeof(double));
		dp = 1;
		targetbytes = dim[0]*dim[1]*dim[2]*dim[3]*sizeof(double);
	}

	readbytes = fpzip_memory_read(in, out, prec, dp, dim[0], dim[1], dim[2], dim[3]);
//	readbytes = fpzip_memory_read(in, out, NULL, dp, dim[0], dim[1], dim[2], dim[3]);
	if (readbytes == inbytes)
		*outbytes = targetbytes;
	else
		*outbytes = -1;
}


static void fpz_compress1D(void *in, unsigned int inbytes, void *out, unsigned int *outbytes, int isfloat)
{
	unsigned int dim[4] = {1, 1, 1, 1};
	int prec[4];
	int dp;

	if (isfloat) {
		dim[0] = inbytes/sizeof(float);
		prec[0]  = (CHAR_BIT * sizeof(float));
		prec[1]  = (CHAR_BIT * sizeof(float));
		prec[2]  = (CHAR_BIT * sizeof(float));
		prec[3]  = (CHAR_BIT * sizeof(float));
		dp = 0;
	}
	else {
		dim[0] = inbytes/sizeof(double);
		prec[0]  = (CHAR_BIT * sizeof(double));
		prec[1]  = (CHAR_BIT * sizeof(double));
		prec[2]  = (CHAR_BIT * sizeof(double));
		prec[3]  = (CHAR_BIT * sizeof(double));
		dp = 1;
	}

	*outbytes = fpzip_memory_write(out, inbytes, in, prec, dp, dim[0], dim[1], dim[2], dim[3]);
//	*outbytes = fpzip_memory_write(out, inbytes, in, NULL, dp, dim[0], dim[1], dim[2], dim[3]);

//	printf("fpz_compress1D: %d -> %d\n", inbytes, *outbytes);
}


static void fpz_decompress1D(char *in, unsigned int inbytes, char *out, unsigned int *outbytes, int isfloat)
{
	unsigned int dim[4] = {1, 1, 1, 1};
	int prec[4];
	int dp;
	int readbytes, targetbytes;

	int adp;
	unsigned int ax, ay, az, af;

	fpzip_memory_get_header((void *)in, &adp, &ax, &ay, &az, &af);
//	printf("%d %d %d %d %d\n", adp, ax, ay, az, af);

	if (isfloat) {
		dim[0] = ax;
		prec[0]  = (CHAR_BIT * sizeof(float));
		prec[1]  = (CHAR_BIT * sizeof(float));
		prec[2]  = (CHAR_BIT * sizeof(float));
		prec[3]  = (CHAR_BIT * sizeof(float));
		dp = 0;
		targetbytes = dim[0]*dim[1]*dim[2]*dim[3]*sizeof(float);
	}
	else {
		dim[0] = ax;
		prec[0]  = (CHAR_BIT * sizeof(double));
		prec[1]  = (CHAR_BIT * sizeof(double));
		prec[2]  = (CHAR_BIT * sizeof(double));
		prec[3]  = (CHAR_BIT * sizeof(double));
		dp = 1;
		targetbytes = dim[0]*dim[1]*dim[2]*dim[3]*sizeof(double);
	}

	readbytes = fpzip_memory_read(in, out, prec, dp, dim[0], dim[1], dim[2], dim[3]);
//	readbytes = fpzip_memory_read(in, out, NULL, dp, dim[0], dim[1], dim[2], dim[3]);

	if (readbytes == inbytes)
		*outbytes = targetbytes;
	else
		*outbytes = -1;
}

//}

