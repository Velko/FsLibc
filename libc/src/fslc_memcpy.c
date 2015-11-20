#include "fslc_string.h"
#include <string.h>

void *fslc_memcpy(void *dest, const void *src, size_t len)
{
    return memcpy(dest, src, len);
}
