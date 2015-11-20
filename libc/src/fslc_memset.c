#include "fslc_string.h"
#include <string.h>

void *fslc_memset(void *ptr, int value, size_t num)
{
    return memset(ptr, value, num);
}
