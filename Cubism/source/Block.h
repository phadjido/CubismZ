/*
 * Block.h
 * Cubism
 *
 * Copyright 2017 ETH Zurich. All rights reserved.
 */
#ifndef _CUBISM_BLOCK_H_
#define _CUBISM_BLOCK_H_

#include <cassert>

namespace cubism {

template <typename T, int SX, int SY, int SZ>
class Block {
public:
    static constexpr int sizeX = SX;
    static constexpr int sizeY = SY;
    static constexpr int sizeZ = SZ;

    static constexpr int sizeArray[3] = {sizeX, sizeY, sizeZ};

    // For CUBISM internals.
    typedef T ElementType;
    typedef T element_type;  // For GridMPI.

    // Data structure to store grid point for this block.
    ElementType data[sizeZ][sizeY][sizeX];

    // Required from Grid.h.
    void clear(void) {
        ElementType *entry = &data[0][0][0];
        const int N = sizeX * sizeY * sizeZ;
        for (int i = 0; i < N; ++i)
            entry[i].clear();
    }

    // Block local grid point access.
    inline ElementType& operator()(int ix, int iy = 0, int iz = 0) {
        assert(ix >= 0 && ix < sizeX);
        assert(iy >= 0 && iy < sizeY);
        assert(iz >= 0 && iz < sizeZ);

        return data[iz][iy][ix];
    }
};

}  // Namespace cubism.

#endif
