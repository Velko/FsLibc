#include "fslc_string.h"
#include "fslc_stringx.h"

char *fslc_strcpy(char *dest, const char *src)
{
    fslc_strcpy_e(dest, src);
    return dest;
}

char *fslc_strcpy_e(char *dest, const char *src)
{
    for(; *src; ++src, ++dest)
        *dest = *src;

    *dest = 0;
    return dest;
}
