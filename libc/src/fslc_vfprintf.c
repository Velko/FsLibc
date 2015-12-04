#include "fslc_stdio.h"

int _fslc_fputs_impl(const char *str, FSLC_FILE *stream);
int _fslc_put_sint(signed int v, FSLC_FILE *stream);
int _fslc_put_uint(unsigned int v, FSLC_FILE *stream);

static int _fslc_vfprintf_impl(FSLC_FILE *stream, const char *format, va_list arg)
{
    int res = 0;
    int pr;
    const char *c;
    
    for (c = format; *c; ++c)
    {
        if (*c == '%')
        {
            ++c;
            switch (*c)
            {
                case 's':
                    pr = _fslc_fputs_impl(va_arg(arg, const char *), stream);
                    if (pr < 0) return pr;
                    res += pr;
                    break;

                case 'c':
                    pr = stream->putc(va_arg(arg, int), stream);
                    if (pr < 0) return pr;
                    ++res;
                    break;
                    
                case '%':
                    pr = stream->putc('%', stream);
                    if (pr < 0) return pr;
                    ++res;
                    break;
                
                case 'i':
                case 'd':
                    pr = _fslc_put_sint(va_arg(arg, signed int), stream);
                    if (pr < 0) return pr;
                    res += pr;
                    break;
                
                case 'u':
                    pr = _fslc_put_uint(va_arg(arg, unsigned int), stream);
                    if (pr < 0) return pr;
                    res += pr;
                    break;            }
        } else {
            pr = stream->putc(*c, stream);
            if (pr < 0) return pr;
            ++res;
        }
    }
    
    return res;
}

int fslc_vfprintf(FSLC_FILE *stream, const char *format, va_list arg)
{
    if (fslc_stdout->pre_output) fslc_stdout->pre_output(fslc_stdout);
    
    int res = _fslc_vfprintf_impl(stream, format, arg);
    
    if (fslc_stdout->post_output) fslc_stdout->post_output(fslc_stdout);
    
    return res;
}

int _fslc_put_sint(signed int v, FSLC_FILE *stream)
{
    if (v < 0)
    {
        int pr = stream->putc('-', stream);
        if (pr < 0) return pr;
        
        int vr = _fslc_put_uint(-v, stream);
        if (vr < 0) return vr;
        
        return vr+1;
    } else
        return _fslc_put_uint(v, stream);
}

int _fslc_put_uint(unsigned int v, FSLC_FILE *stream)
{
    /* Max UInt32 fits in 10 bytes (+1 for zero terminator)
     * 2**32 == 4294967296z
     *          01234567890
     */
    char dbuff[11], *p;

    dbuff[10] = 0;

    for (p = dbuff + 10; v ; v /= 10)
    {
        *(--p) = (v % 10) + '0';
    }

    if (*p == 0) *(--p) = '0';

    return _fslc_fputs_impl(p, stream);
}
