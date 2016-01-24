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

    TEST_FIXTURE(StrModFixture, MultipleSepTest)
    {
        strcpy(testString, "/this/is//file/path/");
        strcpy(expectedString, "/this/is//file/path/");

        char *rsave, *esave;

        char *r1 = fslc_strtok_r(testString, "/", &rsave);
        char *e1 = strtok_r(expectedString, "/", &esave);

        CHECK_EQUAL(e1, r1); // compare strings
        CHECK_EQUAL(e1 - expectedString, r1 - testString); // compare offsets

        char *r2 = fslc_strtok_r(NULL, "/", &rsave);
        char *e2 = strtok_r(NULL, "/", &esave);

        CHECK_EQUAL(e2, r2); // compare strings
        CHECK_EQUAL(e2 - expectedString, r2 - testString); // compare offsets

        char *r3 = fslc_strtok_r(NULL, "/", &rsave);
        char *e3 = strtok_r(NULL, "/", &esave);

        CHECK_EQUAL(e3, r3); // compare strings
        CHECK_EQUAL(e3 - expectedString, r3 - testString); // compare offsets

        char *r4 = fslc_strtok_r(NULL, "/", &rsave);
        char *e4 = strtok_r(NULL, "/", &esave);

        CHECK_EQUAL(e4, r4); // compare strings
        CHECK_EQUAL(e4 - expectedString, r4 - testString); // compare offsets

        char *r5 = fslc_strtok_r(NULL, "/", &rsave);
        char *e5 = strtok_r(NULL, "/", &esave);

        CHECK_EQUAL((uintptr_t)e5, (uintptr_t)r5); // compare pointers (should be NULL)
    }
}
