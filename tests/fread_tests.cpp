#include <UnitTest++.h>

#include "stdio_fixture.h"
#include <string.h>

SUITE(FRead)
{
    TEST_FIXTURE(StdIOFixture, FReadBasicTest)
    {
        uint32_t data[] = { 0x6ba09e07, 0x5f767b19, 0xb4a33cdd, 0x17a64c09, 0x92487695, 0x893092eb, 0 };
        istring.str(std::string((const char *)data));
        
        uint32_t data_read[6];
        
        memset(data_read, 0, sizeof(data_read));
        
        size_t rlen = fslc_fread(data_read, sizeof(uint32_t), 6, &stream);
        
        CHECK_EQUAL(6, rlen);
        
        CHECK_ARRAY_EQUAL(data, data_read, 6);
    }
    
    TEST_FIXTURE(StdIOFixture, FReadEofTest)
    {
        uint32_t data[] = { 0x6ba09e07, 0x5f767b19, 0xb4a33cdd, 0x17a64c09, 0x92487695, 0x890092eb };
        istring.str(std::string((const char *)data));
        
        uint32_t data_read[6];
        
        memset(data_read, 0, sizeof(data_read));
        
        size_t rlen = fslc_fread(data_read, sizeof(uint32_t), 6, &stream);
        
        CHECK_EQUAL(5, rlen);
        
        CHECK_ARRAY_EQUAL(data, data_read, 5);
        CHECK_EQUAL(data[5] & 0x0000FFFF, data_read[5]);
    }
    
    TEST_FIXTURE(StdIOFixture, FReadZeroCountTest)
    {
        uint32_t data_read[6];
        uint32_t data_original[6];
        
        stream.getc = fail_getc;
        
        memset(data_read, 0x20, sizeof(data_read));
        memset(data_original, 0x20, sizeof(data_original));
        
        size_t rlen = fslc_fread(data_read, sizeof(uint32_t), 0, &stream);
        
        CHECK_EQUAL(0, rlen);
        CHECK_EQUAL(0, fail_getc_calls);
        CHECK_ARRAY_EQUAL(data_original, data_read, 6);
    }
    
    TEST_FIXTURE(StdIOFixture, FReadZeroSizeTest)
    {
        uint32_t data_read[6];
        uint32_t data_original[6];
        
        stream.getc = fail_getc;
        
        memset(data_read, 0x20, sizeof(data_read));
        memset(data_original, 0x20, sizeof(data_original));
        
        size_t rlen = fslc_fread(data_read, 0, 6, &stream);
        
        CHECK_EQUAL(0, rlen);
        CHECK_EQUAL(0, fail_getc_calls);
        CHECK_ARRAY_EQUAL(data_original, data_read, 6);
    }
}
