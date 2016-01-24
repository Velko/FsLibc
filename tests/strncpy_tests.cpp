#include <UnitTest++.h>

#include "strmod_fixture.h"
#include <string.h>

SUITE(StrNCpy)
{
    TEST_FIXTURE(StrModFixture, Copy0TerminateTest)
    {
        char *cc = fslc_strncpy(testString,"Hello, World!", 30);
        strncpy(expectedString,"Hello, World!", 30);

        CHECK_EQUAL((uintptr_t)testString, (uintptr_t)cc);

        CHECK_ARRAY_EQUAL(expectedString, testString, strlen(expectedString)+1);
    }

    TEST_FIXTURE(StrModFixture, CopyNTerminateTest)
    {
        char *cc = fslc_strncpy(testString,"Hello, World!", 5);
        strncpy(expectedString,"Hello, World!", 5);

        CHECK_EQUAL((uintptr_t)testString, (uintptr_t)cc);

        CHECK_ARRAY_EQUAL(expectedString, testString, MAXLEN);
    }

    TEST_FIXTURE(StrModFixture, CopyE0TerminateTest)
    {
        char *cc = fslc_strncpy_e(testString,"Hello, World!", 30);
        strncpy(expectedString,"Hello, World!", 30);

        CHECK_EQUAL((uintptr_t)testString+strlen(expectedString), (uintptr_t)cc);

        CHECK_ARRAY_EQUAL(expectedString, testString, strlen(expectedString)+1);
    }

    TEST_FIXTURE(StrModFixture, CopyENTerminateTest)
    {
        char *cc = fslc_strncpy_e(testString,"Hello, World!", 5);
        strncpy(expectedString,"Hello, World!", 5);

        CHECK_EQUAL((uintptr_t)testString+5, (uintptr_t)cc);

        CHECK_ARRAY_EQUAL(expectedString, testString, MAXLEN);
    }
}
