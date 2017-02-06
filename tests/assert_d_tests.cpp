#include <UnitTest++.h>

/* Ensure that desired assertion mode is selected */
#ifdef NDEBUG
#undef NDEBUG
#endif

#include "fslc_assert.h"

SUITE(AssertEnabled)
{
    TEST(AssertPass)
    {
        int val = 4;

        fslc_assert(val == 4);
    }

    TEST(AssertFail)
    {
        int val = 4;

        CHECK_THROW(
            fslc_assert(val == 5),
            UnitTest::AssertException
        );
    }
}

extern "C" void __fslc_assert_fail(const char *expr, const char *file, unsigned int line, const char *)
{
    throw UnitTest::AssertException(expr, file, line);
}
