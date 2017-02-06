#include <UnitTest++.h>
#include "fslc_malloc.h"


SUITE(MallocInternals)
{
// --- initialize_bins ---------------
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

    TEST(CheckLastBinSize)
    {
        bin_t bins[MALLOC_BIN_COUNT];

        initialize_bins(bins);

        CHECK(bins[MALLOC_BIN_COUNT-1].size <= CHUNK_SIZE_MASK);
    }

// --- find_bin_gte ---------------
    TEST(FindGteFirstBinLarger)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_gte(bins, 1);

        CHECK_EQUAL(0, b);
    }

    TEST(FindGteFirstBinEqual)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_gte(bins, bins[0].size);

        CHECK_EQUAL(0, b);
    }

    TEST(FindGteSecondBinLarger)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_gte(bins, CHUNK_MIN_SIZE + 1);

        CHECK_EQUAL(1, b);
    }

    TEST(FindGteSecondBinEqual)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_gte(bins, bins[1].size);

        CHECK_EQUAL(1, b);
    }

    TEST(FindGteEqLastBin)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_gte(bins, bins[MALLOC_BIN_COUNT-1].size);

        CHECK_EQUAL(MALLOC_BIN_COUNT-1, b);
    }

    TEST(FindGteAfterLastBin)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_gte(bins, bins[MALLOC_BIN_COUNT-1].size+1);

        // if target > last bin, returns MALLOC_BIN_COUNT -> unusable index

        CHECK_EQUAL(MALLOC_BIN_COUNT, b);
    }

    TEST(FindGteAllBins)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        /* looping for all possible target sizes is not feasible, therefore we check 3 values
         * (=x-1, =x, =x+1) around each bin size.
         */
        for (size_t b_i = 0; b_i < MALLOC_BIN_COUNT; ++b_i)
            for (size_t target = bins[b_i].size - 1; target <= bins[b_i].size + 1; ++target)
            {
                int b = find_bin_gte(bins, target);

                CHECK(b >= 0);

                if (b < MALLOC_BIN_COUNT)
                {
                    // Normal case - bin found
                    CHECK(bins[b].size >= target);
                    if (b > 0)
                        CHECK(bins[b-1].size < target);
                }
                else
                {
                    // Bin was not found - target too large
                    CHECK_EQUAL(MALLOC_BIN_COUNT, b);
                    CHECK(bins[MALLOC_BIN_COUNT-1].size < target);
                }
            }
    }

// --- find_bin_lte ---------------
    TEST(FindLteFirstBinSmaller)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_lte(bins, bins[0].size + 1);

        CHECK_EQUAL(0, b);
    }

    TEST(FindLteFirstBinEqual)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_lte(bins, bins[0].size);

        CHECK_EQUAL(0, b);
    }

    TEST(FindLteBeforeFirstBin)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_lte(bins, bins[0].size - 1);

        // if target < first bin, returns -1 -> unusable index

        CHECK_EQUAL(-1, b);
    }

    TEST(FindLteSecondBinLarger)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_lte(bins, bins[1].size + 1);

        CHECK_EQUAL(1, b);
    }

    TEST(FindLteSecondBinEqual)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_lte(bins, bins[1].size);

        CHECK_EQUAL(1, b);
    }

    TEST(FindLteEqLastBin)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_lte(bins, bins[MALLOC_BIN_COUNT-1].size);

        CHECK_EQUAL(MALLOC_BIN_COUNT-1, b);
    }

    TEST(FindLteAfterLastBin)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        int b = find_bin_lte(bins, bins[MALLOC_BIN_COUNT-1].size+1);

        // should find last bin
        CHECK_EQUAL(MALLOC_BIN_COUNT-1, b);
    }

    TEST(FindLteAllBins)
    {
        bin_t bins[MALLOC_BIN_COUNT];
        initialize_bins(bins);

        /* looping for all possible target sizes is not feasible, therefore we check 3 values
         * (=x-1, =x, =x+1) around each bin size.
         */
        for (size_t b_i = 0; b_i < MALLOC_BIN_COUNT; ++b_i)
            for (size_t target = bins[b_i].size - 1; target <= bins[b_i].size + 1; ++target)
            {
                int b = find_bin_lte(bins, target);

                CHECK(b < MALLOC_BIN_COUNT);

                if (b >= 0)
                {
                    // Normal case - bin found
                    CHECK(bins[b].size <= target);
                    if (b < MALLOC_BIN_COUNT - 2)
                        CHECK(bins[b+1].size > target);
                }
                else
                {
                    // Bin was not found - target too small
                    CHECK_EQUAL(-1, b);
                    CHECK(bins[0].size > target);
                }
            }
    }
}