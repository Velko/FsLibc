#include <UnitTest++.h>

#include "stdio_fixture.h"

SUITE(FWrite)
{
    TEST_FIXTURE(StdIOFixture, FWriteBasicTest)
    {
        uint32_t data[] = { 0x6ba09e07, 0x5f767b19, 0xb4a33cdd, 0x17a64c09, 0x92487695, 0x853092eb };
        
        int r = fslc_fwrite(data, sizeof(uint32_t), 6, &stream);
        
        CHECK_EQUAL(sizeof(data)/sizeof(uint32_t), r);
        
        std::vector<FuncCallItem> expected_calls;
        unsigned char *c = (unsigned char *)data;
        for (int i = 0; i < sizeof(data); ++i)
            expected_calls.push_back({ CalledFunc::PutC, c[i] });
        
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
    }
    
    TEST_FIXTURE(StdIOFixture, FWritePrePostTest)
    {
        uint32_t data[] = { 0x6ba09e07, 0x5f767b19, 0xb4a33cdd, 0x17a64c09, 0x92487695, 0x853092eb };
        
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        int r = fslc_fwrite(data, sizeof(uint32_t), 6, &stream);
        
        CHECK_EQUAL(sizeof(data)/sizeof(uint32_t), r);
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        unsigned char *c = (unsigned char *)data;
        for (int i = 0; i < sizeof(data); ++i)
            expected_calls.push_back({ CalledFunc::PutC, c[i] });
        expected_calls.push_back({ CalledFunc::PostOp, 0 });
        
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
    }
    
    TEST_FIXTURE(StdIOFixture, FWriteZeroSizeTest)
    {
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        int r = fslc_fwrite(nullptr, 0, 6, &stream);
        
        CHECK_EQUAL(0, r);
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        expected_calls.push_back({ CalledFunc::PostOp, 0 });
        
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
    }
    
    TEST_FIXTURE(StdIOFixture, FWriteZeroCountTest)
    {
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        int r = fslc_fwrite(nullptr, sizeof(uint32_t), 0, &stream);
        
        CHECK_EQUAL(0, r);
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        expected_calls.push_back({ CalledFunc::PostOp, 0 });
        
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
    }
    
    TEST_FIXTURE(StdIOFixture, FWriteEOFTest)
    {
        uint32_t data[] = { 0x6ba09e07, 0x5f767b19, 0xb4a33cdd, 0x17a64c09, 0x92487695, 0x853092eb };
        
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        const int num_eof = 18;
        
        eof_counter = num_eof;
        
        int r = fslc_fwrite(data, sizeof(uint32_t), 6, &stream);
        
        CHECK_EQUAL(num_eof/sizeof(uint32_t), r);
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        unsigned char *c = (unsigned char *)data;
        for (int i = 0; i <= num_eof; ++i)
            expected_calls.push_back({ CalledFunc::PutC, c[i] });
        expected_calls.push_back({ CalledFunc::PostOp, 0 });
        
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
    }
}
