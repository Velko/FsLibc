#include <UnitTest++.h>
#define ALT_FSLC_NAMES /* use alternative FSLC names - do not clash with Host Libc */
#include "fslc_string.h"
#include <string.h>

#include "misc_utils.h"

SUITE(StrNCmp)
{
    TEST(Equal0Test)
    {
        const char *str1 = "Test string";
        const char *str2 = "Test string";

        int r = fslc_strncmp(str1, str2, 20);
        int e = strncmp(str1, str2, 20);

        CHECK_EQUAL(e, r);
    }

    TEST(EqualNTest)
    {
        const char *str1 = "Test string";
        const char *str2 = "Test text";

        int r = fslc_strncmp(str1, str2, 5);
        int e = strncmp(str1, str2, 5);

        CHECK_EQUAL(e, r);
    }

    TEST(Larger0Test)
    {
        const char *str1 = "Test string 1";
        const char *str2 = "Test string 2";

        int r = fslc_strncmp(str1, str2, 20);
        int e = strncmp(str1, str2, 20);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(LargerNTest)
    {
        const char *str1 = "Test 1 string";
        const char *str2 = "Test 2 string";

        int r = fslc_strncmp(str1, str2, 6);
        int e = strncmp(str1, str2, 6);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(Smaller0Test)
    {
        const char *str1 = "Test string 1";
        const char *str2 = "Test string 0";

        int r = fslc_strncmp(str1, str2, 20);
        int e = strncmp(str1, str2, 20);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(SmallerNTest)
    {
        const char *str1 = "Test 1 string";
        const char *str2 = "Test 0 string";

        int r = fslc_strncmp(str1, str2, 6);
        int e = strncmp(str1, str2, 6);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(Longer0Test)
    {
        const char *str1 = "Test string 1";
        const char *str2 = "Test string";

        int r = fslc_strncmp(str1, str2, 20);
        int e = strncmp(str1, str2, 20);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(NotLongerNTest)
    {
        const char *str1 = "Test string 1";
        const char *str2 = "Test string";

        int r = fslc_strncmp(str1, str2, 11);
        int e = strncmp(str1, str2, 11);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(Shorter0Test)
    {
        const char *str1 = "Test string";
        const char *str2 = "Test string 2";

        int r = fslc_strncmp(str1, str2, 20);
        int e = strncmp(str1, str2, 20);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }

    TEST(NotShorterNTest)
    {
        const char *str1 = "Test string";
        const char *str2 = "Test string 2";

        int r = fslc_strncmp(str1, str2, 11);
        int e = strncmp(str1, str2, 11);

        CHECK_EQUAL(SIGNOF(e) , SIGNOF(r));
    }
}
