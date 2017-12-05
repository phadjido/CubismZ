/*
 * hdf2cz.cpp
 * CubismZ
 *
 * Copyright 2017 ETH Zurich. All rights reserved.
 */
#include <map>
#include <iomanip>
#include <iostream>
#include <mpi.h>
using namespace std;
#include "Test_IO_Compressed.h"
#include "ArgumentParser.h"


Simulation * sim = NULL;

int main (int argc, char ** argv)
{
#if defined(_USE_SZ_)
//	SZ_Init((char *)"sz.config");
//	omp_set_num_threads(1);
#endif


	MPI_Init(&argc, &argv);
//	int provided; 
//	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
	
	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	const bool isroot = myrank == 0;
	
	ArgumentParser parser (argc, (const char **)argv);
  
	parser.set_strict_mode();
	
	if (!isroot)
		parser.mute();
  
	sim = new Test_IO_Compressed(isroot, argc, (const char **)argv);
 
	sim->setup();

	sim->dispose();
	
	delete sim;
	
	sim = NULL;
	
	if (isroot) printf("Finishing...\n");
	
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	
	return 0;
}
