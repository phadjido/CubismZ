/*
 * Histogram.h
 * Cubism
 *
 * Copyright 2017 ETH Zurich. All rights reserved.
 */
#pragma once

#include <mpi.h>
#include <vector>
#include <map>
#include <string>

class Histogram
{
    MPI_Comm m_comm;
    std::map<std::string,std::vector<float> > mk2t;
    bool isroot;
    bool bInitialized;
    int reportID;

    void _print2file(std::string sKernel, std::vector<float> & buf);
    void _print_statistcis(std::string sKernel, std::vector<float> & buf);
    void _setup();

public:
    Histogram(const MPI_Comm comm, int a=0): m_comm(comm), mk2t() {}

    void notify(std::string sKernel, float dt);
    void consolidate();
};
