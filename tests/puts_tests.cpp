#include <UnitTest++.h>

#include "stdio_fixture.h"

SUITE(PutS)
{
    TEST_FIXTURE(StdIOFixture, BasicFPutSTest)
    {
        int r = fslc_fputs("ABCD", &stream);
        
        FuncCallItem expected[] = { { CalledFunc::PutC, 'A' }, 
                                    { CalledFunc::PutC, 'B' },
                                    { CalledFunc::PutC, 'C' },
                                    { CalledFunc::PutC, 'D' } };
        
        CHECK(r >= 0);
        CHECK_EQUAL(sizeof(expected)/sizeof(FuncCallItem), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, FuncCallLog.size());
    }
    
    TEST_FIXTURE(StdIOFixture, BasicPutSTest)
    {
        fslc_stdout = &stream;
        
        int r = fslc_puts("ABCD");
        
        FuncCallItem expected[] = { { CalledFunc::PutC, 'A' }, 
                                    { CalledFunc::PutC, 'B' },
                                    { CalledFunc::PutC, 'C' },
                                    { CalledFunc::PutC, 'D' },
                                    { CalledFunc::PutC, '\n'} };
        
        CHECK(r >= 0);
        CHECK_EQUAL(sizeof(expected)/sizeof(FuncCallItem), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, FuncCallLog.size());
    }
    
    TEST_FIXTURE(StdIOFixture, PrePostOpFPutSTest)
    {
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        int r = fslc_fputs("ABCD", &stream);
        
        FuncCallItem expected[] = { { CalledFunc::PreOp, 0 }, 
                                    { CalledFunc::PutC, 'A' }, 
                                    { CalledFunc::PutC, 'B' },
                                    { CalledFunc::PutC, 'C' },
                                    { CalledFunc::PutC, 'D' },
                                    { CalledFunc::PostOp, 0 } };
        
        CHECK(r >= 0);
        CHECK_EQUAL(sizeof(expected)/sizeof(FuncCallItem), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, FuncCallLog.size());
    }
    
    TEST_FIXTURE(StdIOFixture, PrePostOpPutSTest)
    {
        fslc_stdout = &stream;
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        int r = fslc_puts("ABCD");
        
        FuncCallItem expected[] = { { CalledFunc::PreOp, 0 }, 
                                    { CalledFunc::PutC, 'A' }, 
                                    { CalledFunc::PutC, 'B' },
                                    { CalledFunc::PutC, 'C' },
                                    { CalledFunc::PutC, 'D' },
                                    { CalledFunc::PutC, '\n'},
                                    { CalledFunc::PostOp, 0 } };
        
        CHECK(r >= 0);
        CHECK_EQUAL(sizeof(expected)/sizeof(FuncCallItem), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, FuncCallLog.size());
    }
}
