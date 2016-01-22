#include <UnitTest++.h>

#include "stdio_fixture.h"

SUITE(FGetC)
{
    TEST_FIXTURE(StdIOFixture, FGetCBasicTest)
    {
        istring.str("Hello");
        fslc_stdin = &stream;
        
        int h = fslc_getchar();
        int e = fslc_getchar();
        int l1 = fslc_getchar();
        int l2 = fslc_getchar();
        int o = fslc_getchar();
        int ef = fslc_getchar();
        
        CHECK_EQUAL('H', h);
        CHECK_EQUAL('e', e);
        CHECK_EQUAL('l', l1);
        CHECK_EQUAL('l', l2);
        CHECK_EQUAL('o', o);
        CHECK(ef < 0);
    }
    
    TEST_FIXTURE(StdIOFixture, FUnGetCTest)
    {
        istring.str("123");
        
        int c1 = fslc_getc(&stream);
        int r1 = fslc_ungetc('a', &stream);
        int r2 = fslc_ungetc('b', &stream);
        int ca = fslc_getc(&stream);
        int c2 = fslc_getc(&stream);
        
        CHECK_EQUAL('1', c1);
        CHECK_EQUAL('a', r1);
        CHECK(r2 < 0);
        CHECK_EQUAL('a', ca);
        CHECK_EQUAL('2', c2);
    }
}
