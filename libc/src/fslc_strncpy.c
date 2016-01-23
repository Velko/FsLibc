#include "fslc_string.h"
#include <string.h>

char *fslc_strncpy(char *dest, const char *src, size_t len)
{
    return strncpy(dest, src, len);
}
