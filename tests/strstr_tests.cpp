#include <UnitTest++.h>
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
        const char *e = strstr(txt, "m");

        CHECK_EQUAL((uintptr_t)e, (uintptr_t)r); // compare pointer values
    }

    TEST(FindSecond)
    {
        const char *txt = "Test text";

        const char *r = fslc_strstr(txt, "te");
        const char *e = strstr(txt, "te");

        CHECK_EQUAL((uintptr_t)e, (uintptr_t)r);
    }

    TEST(FindSecondLongerTest)
    {
        const char *txt = "Test string";

        const char *r = fslc_strstr(txt, "str");
        const char *e = strstr(txt, "str");

        CHECK_EQUAL((uintptr_t)e, (uintptr_t)r);
    }

    TEST(NotFoundAfter3)
    {
        const char *txt = "Test text";

        const char *r = fslc_strstr(txt, "tu");
        const char *e = strstr(txt, "tu");

        CHECK_EQUAL((uintptr_t)e, (uintptr_t)r);
    }
}
