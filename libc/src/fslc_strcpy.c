#include "fslc_string.h"
#include "fslc_stringx.h"

char *fslc_strcpy(char *dest, const char *src)
{
    fslc_strcpy_e(dest, src);
    return dest;
}
