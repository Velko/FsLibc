#include "fslc_string.h"
#include <string.h>

char *fslc_strpbrk(const char *str, const char *delim)
{
    return strpbrk(str, delim);
}
