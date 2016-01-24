#include "fslc_string.h"

static char *_fslc_strncpy_impl(char *dest, const char *src, size_t len);

char *fslc_strncpy(char *dest, const char *src, size_t len)
{
    _fslc_strncpy_impl(dest, src, len);
    return dest;
}

char *fslc_strncpy_e(char *dest, const char *src, size_t len)
{
    char *r = _fslc_strncpy_impl(dest, src, len);
    return *r ? r + 1: r;
}

static char *_fslc_strncpy_impl(char *dest, const char *src, size_t len)
{
    for(; *src && len > 1; ++src, ++dest, --len)
        *dest = *src;

    *dest = *src;
    return dest;
}
