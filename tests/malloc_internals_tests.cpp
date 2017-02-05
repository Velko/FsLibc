#include <UnitTest++.h>
#include "fslc_malloc.h"


SUITE(MallocInternals)
{
    TEST(InitBinsCheckRange)
    {
        bin_t bins[MALLOC_BIN_COUNT+2];
        bins[0].size = 13;
        bins[MALLOC_BIN_COUNT+1].size = 83;

        initialize_bins(bins+1);
        CHECK_EQUAL(13, bins[0].size);
        CHECK_EQUAL(83, bins[MALLOC_BIN_COUNT+1].size);
    }

    TEST(InitBinsCheckSizesAscending)
    {
        bin_t bins[MALLOC_BIN_COUNT];

        initialize_bins(bins);

        CHECK_EQUAL(CHUNK_MIN_SIZE, bins[0].size);

        for(size_t i = 1; i < MALLOC_BIN_COUNT; ++i)
            CHECK(bins[i-1].size < bins[i].size);
    }
}
