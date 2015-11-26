#include "fslc_string.h"
#include <string.h>

void *fslc_memmove(void *dest, const void *src, size_t len)
{
    return memmove(dest, src, len);
}
