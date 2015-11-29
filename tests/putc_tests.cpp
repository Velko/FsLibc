#include <UnitTest++.h>

#include "stdio_fixture.h"

SUITE(PutC)
{
    TEST_FIXTURE(StdIOFixture, BasicFPutCTest)
    {
        int r = fslc_fputc('A', &stream);
        
        FuncCallItem expected[] = { { CalledFunc::PutC, 'A' } };
        
        CHECK_EQUAL('A', r);
        CHECK_EQUAL(1, FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, 1);
    }
    
    TEST_FIXTURE(StdIOFixture, BasicPutCharTest)
    {
        fslc_stdout = &stream;
        
        int r = fslc_putchar('B');
        
        FuncCallItem expected[] = { { CalledFunc::PutC, 'B' } };
        
        CHECK_EQUAL('B', r);
        CHECK_EQUAL(1, FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, 1);
    }
    
    TEST_FIXTURE(StdIOFixture, PreOpFPutCTest)
    {
        stream.pre_output = fixture_preop;
        int r = fslc_fputc('C', &stream);
        
        FuncCallItem expected[] = { { CalledFunc::PreOp, 0 }, { CalledFunc::PutC, 'C' } };
        
        CHECK_EQUAL('C', r);
        CHECK_EQUAL(2, FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, 2);
    }
    
    TEST_FIXTURE(StdIOFixture, PostpFPutCTest)
    {
        stream.post_output = fixture_postop;
        int r = fslc_fputc('D', &stream);
        
        FuncCallItem expected[] = { { CalledFunc::PutC, 'D' }, { CalledFunc::PostOp, 0 } };
        
        CHECK_EQUAL('D', r);
        CHECK_EQUAL(2, FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, 2);
    }
    
    TEST_FIXTURE(StdIOFixture, PrePostOpFPutCTest)
    {
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        int r = fslc_fputc('E', &stream);
        
        FuncCallItem expected[] = { { CalledFunc::PreOp, 0 }, { CalledFunc::PutC, 'E' }, { CalledFunc::PostOp, 0 } };
        
        CHECK_EQUAL('E', r);
        CHECK_EQUAL(3, FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, 3);
    }
}
