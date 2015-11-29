#include "stdio_fixture.h"

#include <string.h>

StdIOFixture::StdIOFixture()
{
    memset(&stream, 0, sizeof(FSLC_FILE));
    stream.user_ptr = this;
    stream.putc = fixture_putc;        
}

int StdIOFixture::fixture_putc(int c, FSLC_FILE *stream)
{
    auto pf = (StdIOFixture *)stream->user_ptr;
    
    FuncCallItem call;
    
    call.opera = CalledFunc::PutC;
    call.param1 = c;
    
    pf->FuncCallLog.push_back(call);
    
    return c;
}

void StdIOFixture::fixture_preop(FSLC_FILE *stream)
{
    auto pf = (StdIOFixture *)stream->user_ptr;
    
    FuncCallItem call;
    
    call.opera = CalledFunc::PreOp;
    call.param1 = 0;
    
    pf->FuncCallLog.push_back(call);
}

void StdIOFixture::fixture_postop(FSLC_FILE *stream)
{
    auto pf = (StdIOFixture *)stream->user_ptr;
    
    FuncCallItem call;
    
    call.opera = CalledFunc::PostOp;
    call.param1 = 0;
    
    pf->FuncCallLog.push_back(call);
}

std::ostream &operator<< (std::ostream &stream, const StdIOFixture::FuncCallItem &citem)
{
    stream << (int)citem.opera << "(" << citem.param1 << ")";
    return stream;
}
