/*
 *  main.cpp
 *
 *  Created by Panos Hadjidoukas on 4/4/16.
 *  Copyright 2016 ETH Zurich. All rights reserved.
 *
 */

#include <iostream>
#include <mpi.h>

#include "Test_IO_Compressed.h"

using namespace std;

Simulation * sim = NULL;

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	const bool isroot = (rank == 0);
	
	ArgumentParser parser(argc, (const char **)argv);	

	parser.set_strict_mode();
	
	if (!isroot)
		parser.mute();
    
	sim = new Test_IO_Compressed(isroot, argc, (const char **)argv);

	sim->setup();

	sim->dispose();
	delete sim;
	
	sim = NULL;
	
	if (isroot) printf("Finishing...");
	
	MPI_Finalize();
	
	return 0;
}
