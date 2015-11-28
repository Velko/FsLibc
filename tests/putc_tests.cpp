#include <UnitTest++.h>
#define ALT_FSLC_NAMES /* use alternative FSLC names - do not clash with Host Libc */
#include "fslc_stdio.h"
#include <string.h>
#include <vector>


struct PutCFixture
{
    FSLC_FILE stream;
    
    enum struct CalledFunc { None, PreOp, PutC, PostOp };
        
    struct FuncCallItem {
        enum CalledFunc opera;
        int param1;
        bool operator == (const FuncCallItem &other) const
        {
            return opera == other.opera 
                && param1 == other.param1;
        }
    };

    std::vector<FuncCallItem> FuncCallLog;
    
    PutCFixture()
    {
        memset(&stream, 0, sizeof(FSLC_FILE));
        stream.user_ptr = this;
        stream.putc = fixture_putc;        
    }
    
    static int fixture_putc(int c, FSLC_FILE *stream)
    {
        auto pf = (PutCFixture *)stream->user_ptr;
        
        FuncCallItem call;
        
        call.opera = CalledFunc::PutC;
        call.param1 = c;
        
        pf->FuncCallLog.push_back(call);
        
        return c;
    }
    
    static void fixture_preop(FSLC_FILE *stream)
    {
        auto pf = (PutCFixture *)stream->user_ptr;
        
        FuncCallItem call;
        
        call.opera = CalledFunc::PreOp;
        call.param1 = 0;
        
        pf->FuncCallLog.push_back(call);
    }
    
    static void fixture_postop(FSLC_FILE *stream)
    {
        auto pf = (PutCFixture *)stream->user_ptr;
        
        FuncCallItem call;
        
        call.opera = CalledFunc::PostOp;
        call.param1 = 0;
        
        pf->FuncCallLog.push_back(call);
    }    
};

std::ostream &operator<< (std::ostream &stream, const PutCFixture::FuncCallItem &citem)
{
    stream << (int)citem.opera << "(" << citem.param1 << ")";
    return stream;
}


SUITE(PutC)
{
    TEST_FIXTURE(PutCFixture, BasicFPutCTest)
    {
        int r = fslc_fputc('A', &stream);
        
        FuncCallItem expected[] = { { CalledFunc::PutC, 'A' } };
        
        CHECK_EQUAL('A', r);
        CHECK_EQUAL(1, FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, 1);
    }
    
    TEST_FIXTURE(PutCFixture, BasicPutCharTest)
    {
        fslc_stdout = &stream;
        
        int r = fslc_putchar('B');
        
        FuncCallItem expected[] = { { CalledFunc::PutC, 'B' } };
        
        CHECK_EQUAL('B', r);
        CHECK_EQUAL(1, FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, 1);
    }
    
    TEST_FIXTURE(PutCFixture, PreOpFPutCTest)
    {
        stream.pre_output = fixture_preop;
        int r = fslc_fputc('C', &stream);
        
        FuncCallItem expected[] = { { CalledFunc::PreOp, 0 }, { CalledFunc::PutC, 'C' } };
        
        CHECK_EQUAL('C', r);
        CHECK_EQUAL(2, FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, 2);
    }
    
    TEST_FIXTURE(PutCFixture, PostpFPutCTest)
    {
        stream.post_output = fixture_postop;
        int r = fslc_fputc('D', &stream);
        
        FuncCallItem expected[] = { { CalledFunc::PutC, 'D' }, { CalledFunc::PostOp, 0 } };
        
        CHECK_EQUAL('D', r);
        CHECK_EQUAL(2, FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected, FuncCallLog, 2);
    }
    
    TEST_FIXTURE(PutCFixture, PrePostOpFPutCTest)
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
