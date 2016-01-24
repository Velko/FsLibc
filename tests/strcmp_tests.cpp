#include <UnitTest++.h>
#define ALT_FSLC_NAMES /* use alternative FSLC names - do not clash with Host Libc */
#include "fslc_string.h"
#include <string.h>

#include "misc_utils.h"

SUITE(StrCmp)
{
    TEST(EqualTest)
    {
        const char *str1 = "Test string";
        const char *str2 = "Test string";

        int r = fslc_strcmp(str1, str2);
        int e = strcmp(str1, str2);

        CHECK_EQUAL(e, r);
    }

    TEST(LargerTest)
    {
        const char *str1 = "Test string 1";
        const char *str2 = "Test string 2";

        int r = fslc_strcmp(str1, str2);
        int e = strcmp(str1, str2);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(SmallerTest)
    {
        const char *str1 = "Test string 1";
        const char *str2 = "Test string 0";

        int r = fslc_strcmp(str1, str2);
        int e = strcmp(str1, str2);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(LongerTest)
    {
        const char *str1 = "Test string 1";
        const char *str2 = "Test string";

        int r = fslc_strcmp(str1, str2);
        int e = strcmp(str1, str2);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(ShorterTest)
    {
        const char *str1 = "Test string";
        const char *str2 = "Test string 2";

        int r = fslc_strcmp(str1, str2);
        int e = strcmp(str1, str2);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(NegTest)
    {
        const char *str1 = "Test string \xEF";
        const char *str2 = "Test string 2";

        int r = fslc_strcmp(str1, str2);
        int e = strcmp(str1, str2);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }
}
