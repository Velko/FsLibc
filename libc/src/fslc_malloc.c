#include "fslc_stdlib.h"
#include "fslc_malloc.h"

void initialize_bins(struct bin_t *bins)
{
    size_t i;
    size_t chunk_size = 0;
    size_t chunk_increment = CHUNK_MIN_SIZE;

    for (i = 0; i < 64; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^1
    for (; i < 96; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^2
    for (; i < 112; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^3
    for (; i < 120; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^4
    for (; i < 124; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^5
    for (; i < 126; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }

    chunk_increment *= 8; // 8^6
    for (; i < 128; ++i)
    {
        chunk_size += chunk_increment;
        bins[i].size = chunk_size;
    }
}
