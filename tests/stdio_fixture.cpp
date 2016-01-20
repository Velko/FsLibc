#include "stdio_fixture.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

StdIOFixture::StdIOFixture()
{
    memset(&stream, 0, sizeof(FSLC_FILE));
    stream.user_ptr = this;
    stream.putc = fixture_putc;
    eof_counter = -1; // default value = forever
}

int StdIOFixture::fixture_putc(int c, FSLC_FILE *stream)
{
    auto pf = (StdIOFixture *)stream->user_ptr;
    
    FuncCallItem call;
    
    call.opera = CalledFunc::PutC;
    call.param1 = c;
    
    pf->FuncCallLog.push_back(call);
    
    if (pf->eof_counter)
    {
        --pf->eof_counter;
        pf->ostring << (char)c;
        return c;
    }
    else
        return -1;
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

int StdIOFixture::null_putc(int c, FSLC_FILE *stream)
{
    return c;
}

void StdIOFixture::null_prepostop(FSLC_FILE *stream)
{
}

int StdIOFixture::eprintf(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    int len = vsnprintf(nullptr, 0, format, args);
    va_end(args);

    expected_fstring = std::unique_ptr<char>(new char[len+1]);
    char *str = expected_fstring.get();
    
    va_start(args, format);
    vsprintf(str, format, args);
    va_end(args);
    
    return len;
}

std::ostream &operator<< (std::ostream &stream, const StdIOFixture::FuncCallItem &citem)
{
    stream << (int)citem.opera << "(" << citem.param1 << ")";
    return stream;
}
