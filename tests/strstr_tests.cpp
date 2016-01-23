#include <UnitTest++.h>
#define ALT_FSLC_NAMES /* use alternative FSLC names - do not clash with Host Libc */
#include "fslc_string.h"
#include <string.h>

SUITE(StrStr)
{
    TEST(BasicTest)
    {
        const char *txt = "Test string";

        const char *r = fslc_strstr(txt, "st");
        const char *e = strstr(txt, "st");

        CHECK_EQUAL((uintptr_t)e, (uintptr_t)r);
    }

    TEST(NotFoundTest)
    {
        const char *txt = "Test string";

        const char *r = fslc_strstr(txt, "m");
        const char *e = strstr(txt, "mn");

        CHECK_EQUAL((uintptr_t)e, (uintptr_t)r); // compare pointer values
    }
}
