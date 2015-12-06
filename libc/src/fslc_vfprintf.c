#include "fslc_stdio.h"

int _fslc_fputs_impl(const char *str, FSLC_FILE *stream);
int _fslc_put_sint_l(signed long v, FSLC_FILE *stream);
int _fslc_put_uint_l(unsigned long v, FSLC_FILE *stream);

/* There are some considerations when formatting Integers for output:
 *     - on 32-bit systems integers will mostly be 32 bits long, except when one REALLY
 *       wants to print long long. It should be more optimal to use 32-bit calculations
 *       when possible and invoke 64-bit only when needed. To support that we provide 2
 *       separate implementations.
 *     - on 64-bit systems may be 32 or 64 bits, but there is no real benefit from
 *       using shorter bit size. Hence common implementation.
 *     - this library does not aim to support systems with shorter integer sizes (like 16-bit)
 *       but it it did, it would probably make sense to provide optimized ports for these cases
 *       as well.
 * 
 * Buffer size calculations:
 *   Max UInt32 fits in 10 bytes (+1 for zero terminator) decimal
 *   2**32 - 1 == 4294967295z
 *                FFFFFFFFz
 *                01234567890
 * 
 *   Max UInt64 fits in 10 bytes (and +1 for \0)
 *   2**64 -1  == 18446744073709551615z
 *                FFFFFFFFFFFFFFFFz
 *                012345678901234567890
 */

#define BUFSIZE_LONG_LONG_DECIMAL   20
#if __SIZEOF_LONG__ == 4

#define BUFSIZE_LONG_DECIMAL    10
int _fslc_put_sint_ll(signed long long v, FSLC_FILE *stream);
int _fslc_put_uint_ll(unsigned long long v, FSLC_FILE *stream);

#elif __SIZEOF_LONG__ == 8

#define BUFSIZE_LONG_DECIMAL    BUFSIZE_LONG_LONG_DECIMAL
#define _fslc_put_sint_ll   _fslc_put_sint_l
#define _fslc_put_uint_ll   _fslc_put_uint_l

#endif


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
                    pr = _fslc_put_sint_l(va_arg(arg, signed int), stream);
                    if (pr < 0) return pr;
                    res += pr;
                    break;
                
                case 'u':
                    pr = _fslc_put_uint_l(va_arg(arg, unsigned int), stream);
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

int _fslc_put_sint_l(signed long v, FSLC_FILE *stream)
{
    if (v < 0)
    {
        int pr = stream->putc('-', stream);
        if (pr < 0) return pr;
        
        pr = _fslc_put_uint_l(-v, stream);
        if (pr < 0) return pr;
        
        return pr+1;
    } else
        return _fslc_put_uint_l(v, stream);
}

int _fslc_put_uint_l(unsigned long v, FSLC_FILE *stream)
{
    char dbuff[BUFSIZE_LONG_DECIMAL+1], *p;

    dbuff[BUFSIZE_LONG_DECIMAL] = 0;

    for (p = dbuff + BUFSIZE_LONG_DECIMAL; v ; v /= 10)
    {
        *(--p) = (v % 10) + '0';
    }

    if (*p == 0) *(--p) = '0';

    return _fslc_fputs_impl(p, stream);
}

#if __SIZEOF_LONG__ == 4

int _fslc_put_sint_ll(signed long long v, FSLC_FILE *stream)
{
    if (v < 0)
    {
        int pr = stream->putc('-', stream);
        if (pr < 0) return pr;
        
        pr = _fslc_put_uint_l(-v, stream);
        if (pr < 0) return pr;
        
        return pr+1;
    } else
        return _fslc_put_uint_ll(v, stream);
}

int _fslc_put_uint_ll(unsigned long long v, FSLC_FILE *stream)
{
    char dbuff[BUFSIZE_LONG_LONG_DECIMAL+1], *p;

    dbuff[BUFSIZE_LONG_LONG_DECIMAL] = 0;

    for (p = dbuff + BUFSIZE_LONG_LONG_DECIMAL; v ; v /= 10)
    {
        *(--p) = (v % 10) + '0';
    }

    if (*p == 0) *(--p) = '0';

    return _fslc_fputs_impl(p, stream);
}

#endif
