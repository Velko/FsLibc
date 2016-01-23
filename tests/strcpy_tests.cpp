#include <UnitTest++.h>

#include "strmod_fixture.h"
#include <string.h>

SUITE(StrCpy)
{
    TEST_FIXTURE(StrModFixture, BasicTest)
    {
        char *cc = fslc_strcpy(testString,"Hello, World!");
        strcpy(expectedString,"Hello, World!");

        CHECK_EQUAL((uintptr_t)testString, (uintptr_t)cc);

        CHECK_ARRAY_EQUAL(expectedString, testString, MAXLEN);
    }
}
