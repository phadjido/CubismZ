/*
 * cz2hdf.cpp
 * CubismZ
 *
 * Copyright 2017 ETH Zurich. All rights reserved.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <mpi.h>
#include <hdf5.h>
#include <H5FDmpio.h>
#define _PARALLEL_IO_
#define _COLLECTIVE_IO_
//#define _TRANSPOSE_DATA_

#ifdef _FLOAT_PRECISION_
#define H5T_NATIVE_FP   H5T_NATIVE_FLOAT
#else
#define H5T_NATIVE_FP   H5T_NATIVE_DOUBLE
#endif

#include "ArgumentParser.h"
#include "Reader_WaveletCompression.h"

int main(int argc, char **argv)
{
	/* Initialize MPI */
        int provided;
        MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

	const double init_t0 = MPI_Wtime();

	/* MPI variables */
	MPI_Comm comm  = MPI_COMM_WORLD;
	MPI_Info info  = MPI_INFO_NULL;

	int mpi_rank, mpi_size;

	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

	const bool isroot = !mpi_rank;

	ArgumentParser argparser(argc, (const char **)argv);

	if (isroot)
		argparser.loud();
	else
		argparser.mute();

	string inputfile_name[3];
	inputfile_name[0]= argparser("-simdata").asString("none");
	inputfile_name[1] = argparser("-simdata2").asString("none");
	inputfile_name[2] = argparser("-simdata3").asString("none");
	const string h5file_name = argparser("-h5file").asString("none");

	if ((inputfile_name[0] == "none")||(h5file_name == "none"))
	{
		printf("usage: %s -simdata <filename> [-simdata2 <filename>] [simdata3 <filename>] -h5file <h5basefilename> [-swap] [-wtype <wtype>] [-xs <x0>] [-xe <x1>] [-ys <y0>] [-ye <y1>] [-zs <z0>] [-ze <z1>]\n", argv[0]);
		exit(1);
	}

	int NCHANNELS = 1;
	if ((inputfile_name[1] != "none")) NCHANNELS++;
	if ((inputfile_name[2] != "none")) NCHANNELS++;

	const int Xs = argparser("-xs").asInt(-1);
	const int Xe = argparser("-xe").asInt(-1);
	const int Ys = argparser("-ys").asInt(-1);
	const int Ye = argparser("-ye").asInt(-1);
	const int Zs = argparser("-zs").asInt(-1);
	const int Ze = argparser("-ze").asInt(-1);

	const bool swapbytes = argparser.check("-swap");
	const int wtype = argparser("-wtype").asInt(1);

	/* HDF5 APIs definitions */
	hid_t file_id, dset_id; /* file and dataset identifiers */
	hid_t filespace, memspace;      /* file and memory dataspace identifiers */
	hid_t nullmemspace;
	hsize_t dims[4]; /* dataset dimensions */
	hsize_t	count[4];	  /* hyperslab selection parameters */
	hsize_t	offset[4];
	hid_t	plist_id; /* property list identifier */
	herr_t	status;

	Reader_WaveletCompressionMPI *myreader[NCHANNELS];

	for (int i = 0; i < NCHANNELS; i++)
		myreader[i] =  new Reader_WaveletCompressionMPI (comm, inputfile_name[i], swapbytes, wtype);
	
	for (int i = 0; i < NCHANNELS; i++)
		myreader[i]->load_file();

	const double init_t1 = MPI_Wtime();

	const double t0 = MPI_Wtime(); 

	string h5file_fullname = h5file_name + ".h5";

	/*  Set up file access property list with parallel I/O access */
	plist_id = H5Pcreate(H5P_FILE_ACCESS);
#if defined(_PARALLEL_IO_)
	H5Pset_fapl_mpio(plist_id, comm, info);
#endif
	/* Create a new file collectively and release property list identifier. */
	file_id = H5Fcreate(h5file_fullname.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, plist_id);
	H5Pclose(plist_id);

	int NBX = myreader[0]->xblocks();
	int NBY = myreader[0]->yblocks();
	int NBZ = myreader[0]->zblocks();
	fprintf(stdout, "I found in total %dx%dx%d blocks.\n", NBX, NBY, NBZ);

	int StartX, StartY, StartZ;
	int EndX, EndY, EndZ;
	
	if (Xs == -1)
		StartX = 0;
	else
		StartX = Xs;
	
	if (Xe == -1)
		EndX = NBX-1;
	else
		EndX = Xe;

	if (Ys == -1)
		StartY = 0;
	else
		StartY = Ys;
	
	if (Ye == -1)
		EndY = NBY-1;
	else
		EndY = Ye;

	if (Zs == -1)
		StartZ = 0;
	else
		StartZ = Zs;
	
	if (Ze == -1)
		EndZ = NBZ-1;
	else
		EndZ = Ze;

	fprintf(stdout, "ROI = [%d,%d]x[%d,%d]x[%d,%d]\n", StartX, EndX, StartY, EndY, StartZ, EndZ);	
	
	int NX = (EndX-StartX+1)*_BLOCKSIZE_;
	int NY = (EndY-StartY+1)*_BLOCKSIZE_;
	int NZ = (EndZ-StartZ+1)*_BLOCKSIZE_;

	/* Create the dataspace for the dataset.*/
#if defined(_TRANSPOSE_DATA_)
	dims[0] = NX;
	dims[1] = NY;
	dims[2] = NZ;
	dims[3] = NCHANNELS;
#else
	dims[0] = NZ;
	dims[1] = NY;
	dims[2] = NX;
	dims[3] = NCHANNELS;
#endif
	filespace = H5Screate_simple(4, dims, NULL);

	/* Create the dataset with default properties and close filespace.*/
#ifndef _ON_FERMI_
	dset_id = H5Dcreate(file_id, "data", H5T_NATIVE_FP, filespace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
#else
        dset_id = H5Dcreate2(file_id, "data", H5T_NATIVE_FP, filespace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
#endif
	H5Sclose(filespace);

	count[0] = _BLOCKSIZE_;
	count[1] = _BLOCKSIZE_;
	count[2] = _BLOCKSIZE_;
	count[3] = NCHANNELS;
	memspace = H5Screate_simple(4, count, NULL);
	nullmemspace = H5Screate_simple(4, count, NULL);


	/* Create property list for collective dataset write. */
	plist_id = H5Pcreate(H5P_DATASET_XFER);
#if defined(_COLLECTIVE_IO_)
	H5Pset_dxpl_mpio(plist_id, H5FD_MPIO_COLLECTIVE);
#endif	

	static Real *targetdata_all;
	targetdata_all = (Real *)malloc(_BLOCKSIZE_*_BLOCKSIZE_*_BLOCKSIZE_*NCHANNELS*sizeof(Real));
	static Real targetdata[_BLOCKSIZE_][_BLOCKSIZE_][_BLOCKSIZE_];

#if defined(_TRANSPOSE_DATA_)
	static Real *storedata;
	storedata = (Real *)malloc(_BLOCKSIZE_*_BLOCKSIZE_*_BLOCKSIZE_*NCHANNELS*sizeof(Real));
#endif

	const int nblocks = NBX*NBY*NBZ;
	const int b_end = ((nblocks + (mpi_size - 1))/ mpi_size) * mpi_size; 

	for (int b = mpi_rank; b < b_end; b += mpi_size)	
	{
#if defined(_TRANSPOSE_DATA_)
		int x = b / (NBY * NBZ);
		int y = (b / NBZ) % NBY;
		int z = b % NBZ;
#else
		int z = b / (NBY * NBX);
		int y = (b / NBX) % NBY;
		int x = b % NBX;
#endif
		int in_roi = (StartX <= x) && (x <= EndX) && (StartY <= y) && (y <= EndY) && (StartZ <= z) && (z <= EndZ);  
		if ((b < nblocks) && (in_roi))
		{
#if defined(VERBOSE)
			fprintf(stdout, "loading block( %d, %d, %d )...\n", x, y, z); 
#endif

			memset(targetdata_all, 0, NCHANNELS*_BLOCKSIZE_*_BLOCKSIZE_*_BLOCKSIZE_*sizeof(Real));

			for (int i = 0; i < NCHANNELS; i++)
			{
			double zratio = myreader[i]->load_block2(x, y, z, targetdata);
			(void)zratio;
#if defined(VERBOSE)
			fprintf(stdout, "compression ratio was %.2lf\n", zratio); 
#endif

			for (int xb = 0; xb < _BLOCKSIZE_; xb++)
				for (int yb = 0; yb < _BLOCKSIZE_; yb++)
					for (int zb = 0; zb < _BLOCKSIZE_; zb++)
					{
						targetdata_all[i + zb*NCHANNELS + yb*NCHANNELS*_BLOCKSIZE_ + xb*NCHANNELS*_BLOCKSIZE_*_BLOCKSIZE_] = targetdata[xb][yb][zb];
					}
			}
			
#if defined(_TRANSPOSE_DATA_)
			for (int i = 0; i < NCHANNELS; i++)
			{
			for (int xb = 0; xb < _BLOCKSIZE_; xb++)
				for (int yb = 0; yb < _BLOCKSIZE_; yb++)
					for (int zb = 0; zb < _BLOCKSIZE_; zb++) {
						storedata[i + xb*NCHANNELS + yb*NCHANNELS*_BLOCKSIZE_ + zb*NCHANNELS*_BLOCKSIZE_*_BLOCKSIZE_] = 
						targetdata_all[i + zb*NCHANNELS + yb*NCHANNELS*_BLOCKSIZE_ + xb*NCHANNELS*_BLOCKSIZE_*_BLOCKSIZE_];

					}
			}

			offset[0] = (x - StartX) * count[0];
			offset[1] = (y - StartY) * count[1];
			offset[2] = (z - StartZ) * count[2];
			offset[3] = 0;
#else
			offset[0] = (z-StartZ) * count[0];
			offset[1] = (y-StartY) * count[1];
			offset[2] = (x-StartX) * count[2];
			offset[3] = 0;
#endif


			/* Select hyperslab in the file */
			filespace = H5Dget_space(dset_id);
			H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);

#if defined(_TRANSPOSE_DATA_)
			status = H5Dwrite(dset_id, H5T_NATIVE_FP, memspace, filespace, plist_id, storedata);
#else
			status = H5Dwrite(dset_id, H5T_NATIVE_FP, memspace, filespace, plist_id, targetdata_all);
#endif
			H5Sclose(filespace);
		}
		else {
			offset[0] = 0;
			offset[1] = 0;
			offset[2] = 0;
			offset[3] = 0;

			H5Sselect_none(nullmemspace);
			
			filespace = H5Dget_space(dset_id);
			H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);
			H5Sselect_none(filespace);
			
			status = H5Dwrite(dset_id, H5T_NATIVE_FP, nullmemspace, filespace, plist_id, NULL);

		}
	}

	MPI_Barrier(MPI_COMM_WORLD);
	const double t1 = MPI_Wtime(); 

	if (!mpi_rank)
	{
		fprintf(stdout, "Init time = %.3lf seconds\n", init_t1-init_t0);
		fprintf(stdout, "Elapsed time = %.3lf seconds\n", t1-t0);
		fflush(0);
	}
	

	/* Close/release resources */
	for (int channel = 0; channel < NCHANNELS; channel++)
	{
		delete myreader[channel];
	}

	H5Sclose(memspace);
	H5Sclose(nullmemspace);
	H5Dclose(dset_id);
	H5Pclose(plist_id);
	H5Fclose(file_id);

	if (!mpi_rank)
	{
		// prepare the xmf file
		char wrapper[256];
		sprintf(wrapper, "%s.xmf", h5file_name.c_str());
		FILE *xmf = 0;
		xmf = fopen(wrapper, "w");
		fprintf(xmf, "<?xml version=\"1.0\" ?>\n");
		fprintf(xmf, "<!DOCTYPE Xdmf SYSTEM \"Xdmf.dtd\" []>\n");
		fprintf(xmf, "<Xdmf Version=\"2.0\">\n");
		fprintf(xmf, " <Domain>\n");
		fprintf(xmf, "   <Grid GridType=\"Uniform\">\n");
		fprintf(xmf, "     <Time Value=\"%05d\"/>\n", 0);
		fprintf(xmf, "     <Topology TopologyType=\"3DCORECTMesh\" Dimensions=\"%d %d %d\"/>\n", (int)dims[0], (int)dims[1], (int)dims[2]);
		fprintf(xmf, "     <Geometry GeometryType=\"ORIGIN_DXDYDZ\">\n");
#ifdef _FLOAT_PRECISION_
		fprintf(xmf, "       <DataItem Name=\"Origin\" Dimensions=\"3\" NumberType=\"Float\" Precision=\"4\" Format=\"XML\">\n");
#else
		fprintf(xmf, "       <DataItem Name=\"Origin\" Dimensions=\"3\" NumberType=\"Double\" Precision=\"8\" Format=\"XML\">\n");
#endif
		fprintf(xmf, "        %e %e %e\n", 0.,0.,0.);
		fprintf(xmf, "       </DataItem>\n");
#ifdef _FLOAT_PRECISION_
		fprintf(xmf, "       <DataItem Name=\"Spacing\" Dimensions=\"3\" NumberType=\"Float\" Precision=\"4\" Format=\"XML\">\n");
#else
		fprintf(xmf, "       <DataItem Name=\"Spacing\" Dimensions=\"3\" NumberType=\"Double\" Precision=\"8\" Format=\"XML\">\n");
#endif

		fprintf(xmf, "        %e %e %e\n", 1./(Real)max(dims[0],max(dims[1],dims[2])),1./(Real)max(dims[0],max(dims[1],dims[2])),1./(Real)max(dims[0],max(dims[1],dims[2])));
		fprintf(xmf, "       </DataItem>\n");
		fprintf(xmf, "     </Geometry>\n");

		if (NCHANNELS == 1)
			fprintf(xmf, "     <Attribute Name=\"data\" AttributeType=\"%s\" Center=\"Node\">\n", "Scalar");
		else
			fprintf(xmf, "     <Attribute Name=\"data\" AttributeType=\"%s\" Center=\"Node\">\n", "Vector");

#ifdef _FLOAT_PRECISION_
		fprintf(xmf, "       <DataItem Dimensions=\"%d %d %d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", (int)dims[0], (int)dims[1], (int)dims[2], (int)dims[3]);
#else
		fprintf(xmf, "       <DataItem Dimensions=\"%d %d %d %d\" NumberType=\"Float\" Precision=\"8\" Format=\"HDF\">\n", (int)dims[0], (int)dims[1], (int)dims[2], (int)dims[3]);
#endif

		string str = h5file_fullname;
		unsigned found = str.find_last_of("/");
		str = str.substr(found+1);

		fprintf(xmf, "        %s:/data\n", str.c_str());

		fprintf(xmf, "       </DataItem>\n");
		fprintf(xmf, "     </Attribute>\n");

		fprintf(xmf, "   </Grid>\n");
		fprintf(xmf, " </Domain>\n");
		fprintf(xmf, "</Xdmf>\n");
		fclose(xmf);
	}
	
	MPI_Finalize();

	return 0;
}
