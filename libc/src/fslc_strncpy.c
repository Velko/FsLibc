#include "fslc_string.h"

char *fslc_strncpy(char *dest, const char *src, size_t len)
{
    fslc_strncpy_e(dest, src, len);
    return dest;
}

char *fslc_strncpy_e(char *dest, const char *src, size_t len)
{
    for(; *src && len > 1; ++src, ++dest, --len)
        *dest = *src;

    *dest = *src;
    return dest;
}
