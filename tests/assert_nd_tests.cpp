#include <UnitTest++.h>

/* Ensure that desired assertion mode is selected */
#ifndef NDEBUG
#define NDEBUG
#endif

#include "fslc_assert.h"

SUITE(AssertDisabled)
{
    TEST(AssertPass)
    {
        int val = 4;

        fslc_assert(val == 4);
    }

    TEST(AssertFailIgnored)
    {
        int val = 4;

        fslc_assert(val == 5);
    }
}
