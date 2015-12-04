#include "fslc_stdio.h"

int _fslc_fputs_impl(const char *str, FSLC_FILE *stream);

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
            }
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
