/*
 * Timer.h
 * Cubism
 *
 * Copyright 2017 ETH Zurich. All rights reserved.
 */

#pragma once
#include <sys/time.h>

class Timer
{
	struct timeval t_start, t_end;
	struct timezone t_zone;
	
public:
	
	void start()
	{
		gettimeofday(&t_start,  &t_zone);
	}
	
	double stop()
	{
		gettimeofday(&t_end,  &t_zone);
		return (t_end.tv_usec  - t_start.tv_usec)*1e-6  + (t_end.tv_sec  - t_start.tv_sec);
	}
};
