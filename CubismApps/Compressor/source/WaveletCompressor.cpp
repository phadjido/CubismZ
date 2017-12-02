/*
 *  WaveletCompressor.cpp
 *  
 *
 *  Created by Diego Rossinelli on 3/4/13.
 *  Copyright 2013 ETH Zurich. All rights reserved.
 *
 */

#ifdef _SP_COMP_
typedef float Real;
#else
typedef double Real;
#endif

#include <cstdio>
#include <bitset>
#include <cassert>

using namespace std;

#include "WaveletCompressor.h"

void swapbytes(unsigned char *mem, int nbytes)
{
        unsigned char buf[8];
        for (int i = 0; i < nbytes; i++) buf[i] = mem[i];
        for (int i = 0; i < nbytes; i++) mem[nbytes-i-1] = buf[i];
}


#if defined(_USE_ZEROBITS_)
void float_zero_bits3(unsigned int *ul, int n)
{
        unsigned int _ul = *ul;
        unsigned long mask = ~((1 << n) - 1);
        _ul = _ul & mask;

        *ul = _ul;


}

float float_zero_bits3b(float x, int bits)
{
        union { int ix; float fx; } v;
        v.fx = x;
        v.ix &= ~((1 << bits) - 1);

        return v.fx;
}
#endif

#if defined(_USE_SHUFFLE3_)
static void shuffle3(char *in, int n, int s)
{
	int i, j, b;
	char *tmp = (char *)malloc(n);

	j = 0;
	for (b = 0; b < s; b++)
	{
		for (i = b; i < n; i+= s)
		{
			tmp[j] = in[i];
			j++;
		}
	}

	memcpy(in, tmp, n);
	free(tmp);
}

void reshuffle3(char *in, int n, int s)
{
	int i, j, b;
	char *tmp = (char *)malloc(n);

	int c = n/s;

	j = 0;
	for (i = 0; i < n/s; i++)
	{
		for (b = 0; b < s; b++)
		{
			tmp[j] = in[i + b*c]; j++;
		}
	}

	memcpy(in, tmp, n);
	free(tmp);
}

#endif

template<int N>
void serialize_bitset(bitset<N> mybits, unsigned char * const buf, const int nbytes)
{
	assert(nbytes == (N + 7) / 8);
	
	const int nicebits = 8 * (N / 8);
	
	for(int i = 0, B = 0; i < nicebits; i += 8, ++B)
	{
		unsigned char c = 0;
		
		for(int b = 0; b < 8; ++b)
			c |= mybits[i + b] << b;
		
		buf[B] = c;
	}
	
	if (nicebits < N)
	{
		unsigned char c = 0;
		
		for(int b = nicebits; b < N; ++b)
			c |= mybits[b] << (b - nicebits);
		
		buf[nbytes - 1] = c;
	}
}

template<int N>
int deserialize_bitset(bitset<N>& mybits, const unsigned char * const buf, const int nbytes)
{
	assert(nbytes == (N + 7) / 8);
	
	int sum = 0;
	
	const int nicebits = 8 * (N / 8);
	
	for(int i = 0, B = 0; i < nicebits; i += 8, ++B)
	{
		const unsigned char c = buf[B];
		
		for(int b = 0; b < 8; ++b)
			sum += (mybits[i + b] = (c >> b) & 1);		
	}
	
	if (nicebits < N)
	{
		const unsigned char c = buf[nbytes - 1];
		
		for(int b = nicebits; b < N; ++b)
			sum += (mybits[b] = (c >> (b - nicebits)) & 1);
	}
	
	return sum;
}

unsigned short _cvt2f16(const float xfloat)
{
	assert(sizeof(unsigned short) == 2);
	
	const unsigned int x = *(unsigned int *)& xfloat;
	
	//copy sign
	unsigned short retval = (x & 0x80000000) >> 16; 
	
	//reshape exponent
	const int e = ((x & 0x7fffffff) >> 23) - 127;
	retval |= max(0, min(31, e + 15)) << 10;
	
	//reshape mantissa
	const unsigned int m = x & 0x007fffff;
	retval |= m >> 13;
	
	return retval;
}

float _cvtfromf16(const unsigned short f16)
{
	//copy sign
	int retval = (f16 & 0x8000) << 16;
	
	//reshape exponent
	const int e = (((0x1f << 10) & f16) >> 10) - 15;
	retval |= (e + 127) << 23;
	
	//reshape mantissa
	const int m = f16 & 0x3ff;
	retval |= m << 13;
	
	return *(float *)& retval;
}

template<int DATASIZE1D, typename DataType>
size_t WaveletCompressorGeneric<DATASIZE1D, DataType>::compress(const float threshold, const bool float16, int wtype)
{				
	full.fwt(wtype);
	
	assert(BITSETSIZE % sizeof(DataType) == 0);
	
	bitset<BS3> mask;
	const int survivors = full.template threshold<DataType, DATASIZE1D>(threshold, mask, (DataType *)(bufcompression + BITSETSIZE));

	serialize_bitset<BS3>(mask, bufcompression, BITSETSIZE);

#if defined(_USE_SHUFFLE3_)||defined(_USE_ZEROBITS_)

  #if defined(_USE_ZEROBITS_)
	// set some bits to zero
	for(int i = 0; i < survivors; ++i) 
	{
		DataType *ps = (i + (DataType *)(bufcompression + BITSETSIZE));
		float_zero_bits3((unsigned int *)ps, _ZEROBITS_);	// xxx: extend it for doubles
	}
  #endif

  #if defined(_USE_SHUFFLE3_)
	shuffle3((char *)(bufcompression + BITSETSIZE), survivors*sizeof(DataType), sizeof(DataType));
  #endif

#endif

	return BITSETSIZE + sizeof(DataType) * survivors;
}


template<int DATASIZE1D, typename DataType>
size_t WaveletCompressorGeneric<DATASIZE1D, DataType>::compress(const float threshold, const bool float16, bool swap, int wtype)
{				
	full.fwt(wtype);
	
	exit(1);
	assert(BITSETSIZE % sizeof(DataType) == 0);
	
	bitset<BS3> mask;
	const int survivors = full.template threshold<DataType, DATASIZE1D>(threshold, mask, (DataType *)(bufcompression + BITSETSIZE));

	serialize_bitset<BS3>(mask, bufcompression, BITSETSIZE);

#if defined(_USE_SHUFFLE3_)||defined(_USE_ZEROBITS_)

  #if defined(_USE_ZEROBITS_)
	// set some bits to zero
	for(int i = 0; i < survivors; ++i) 
	{
		DataType *ps = (i + (DataType *)(bufcompression + BITSETSIZE));
		float_zero_bits3((unsigned int *)ps, _ZEROBITS_);	// xxx: extend it for doubles
	}
  #endif


	// peh: need to verify if this is the correct place for byte swapping. However, swapping is in general useless for the compression tool.
	if (swap)
	{
		unsigned char *buf = ((unsigned char *)bufcompression + BITSETSIZE);
		int sz = sizeof(DataType);	// = 4
		for(int i = 0; i < survivors; ++i) {
			swapbytes((unsigned char *)buf+i*sz, sz);
		}
	}


  #if defined(_USE_SHUFFLE3_)
	shuffle3((char *)(bufcompression + BITSETSIZE), survivors*sizeof(DataType), sizeof(DataType));
  #endif

#endif

	return BITSETSIZE + sizeof(DataType) * survivors;
	
}


template<int DATASIZE1D, typename DataType>
void WaveletCompressorGeneric<DATASIZE1D, DataType>::decompress(const bool float16, size_t bytes, int wtype)
{
	bitset<BS3> mask;
	const int expected = deserialize_bitset<BS3>(mask, bufcompression, BITSETSIZE);

#if defined(_USE_SHUFFLE3_)
	reshuffle3((char *)(bufcompression + BITSETSIZE), bytes - BITSETSIZE, sizeof(DataType));
#endif

	assert((bytes - sizeof(bitset<BS3>)) % sizeof(DataType) == 0 || float16);
	assert((bytes - sizeof(bitset<BS3>)) % sizeof(unsigned short) == 0);
	
	size_t bytes_read = BITSETSIZE;
	
	//const
	int nelements = (bytes - bytes_read) / (float16 ? sizeof(unsigned short) : sizeof(DataType));
	if (nelements - expected == 1) {
		nelements--;
	}
	assert(expected == nelements);
	
	vector<DataType> datastream(nelements);
	
	memcpy((void *)&datastream.front(), bufcompression + bytes_read, sizeof(DataType) * nelements);	
	
	full.load(datastream, mask);
	full.iwt(wtype);
}

#ifdef _BLOCKSIZE_
template class WaveletCompressorGeneric<_BLOCKSIZE_, Real>;
template class WaveletCompressorGeneric_zlib<_BLOCKSIZE_, Real>;
#endif

#ifdef _VOXELS_ //mammamia whattahack
template class WaveletCompressorGeneric<_VOXELS_, float>;
template class WaveletCompressorGeneric_zlib<_VOXELS_, float>;
#endif
