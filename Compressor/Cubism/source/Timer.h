/*
 * Timer.h
 * Cubism
 *
 * Copyright 2018 ETH Zurich. All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
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
