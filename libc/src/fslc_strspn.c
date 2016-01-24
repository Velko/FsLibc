#include "fslc_string.h"
#include <string.h>

size_t fslc_strspn(const char *str, const char *delim)
{
    return strspn(str, delim);
}
