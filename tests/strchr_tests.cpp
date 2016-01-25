#include <UnitTest++.h>
#include "fslc_string.h"
#include <string.h>

SUITE(StrChr)
{
    TEST(BasicTest)
    {
        const char *txt = "Test string";

        const char *r = fslc_strchr(txt, 's');
        const char *e = strchr(txt, 's');

        CHECK_EQUAL((uintptr_t)e, (uintptr_t)r);
    }

    TEST(NotFoundTest)
    {
        const char *txt = "Test string";

        const char *r = fslc_strchr(txt, 'm');
        const char *e = strchr(txt, 'm');

        CHECK_EQUAL((uintptr_t)e, (uintptr_t)r); // compare pointer values
    }
}
