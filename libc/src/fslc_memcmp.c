#include "fslc_string.h"
#include <string.h>

int fslc_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    return memcmp(ptr1, ptr2, num);
}
