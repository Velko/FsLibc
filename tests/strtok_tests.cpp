#include <UnitTest++.h>

#include "strmod_fixture.h"
#include <string.h>

SUITE(StrTok)
{
    TEST_FIXTURE(StrModFixture, BasicParseTest)
    {
        strcpy(testString, "Delimited,string;by.some-chars");
        strcpy(expectedString, "Delimited,string;by.some-chars");

        char *rsave, *esave;

        char *r1 = fslc_strtok_r(testString, "-.;,", &rsave);
        char *e1 = strtok_r(expectedString, "-.;,", &esave);

        CHECK_EQUAL(e1, r1); // compare strings
        CHECK_EQUAL(e1 - expectedString, r1 - testString); // compare offsets

        char *r2 = fslc_strtok_r(NULL, "-.;,", &rsave);
        char *e2 = strtok_r(NULL, "-.;,", &esave);

        CHECK_EQUAL(e2, r2); // compare strings
        CHECK_EQUAL(e2 - expectedString, r2 - testString); // compare offsets

        CHECK_ARRAY_EQUAL(expectedString, testString, MAXLEN);
    }

    TEST_FIXTURE(StrModFixture, NotFoundTest)
    {
        strcpy(testString, "Delimited,string;by.some-chars");
        strcpy(expectedString, "Delimited,string;by.some-chars");

        char *rsave, *esave;

        char *r1 = fslc_strtok_r(testString, "!@#", &rsave);
        char *e1 = strtok_r(expectedString, "!@#", &esave);

        CHECK_EQUAL(e1, r1); // compare strings
        CHECK_EQUAL(e1 - expectedString, r1 - testString); // compare offsets

        char *r2 = fslc_strtok_r(NULL, "!@#", &rsave);

        CHECK_EQUAL(NULL, (uintptr_t)r2);

        CHECK_ARRAY_EQUAL(expectedString, testString, MAXLEN);

        char *r3 = fslc_strtok_r(NULL, "!@#", &rsave);

        CHECK_EQUAL(NULL, (uintptr_t)r3);
    }
}
