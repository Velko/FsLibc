#include "fslc_string.h"
#include <string.h>

int fslc_strncmp(const char *str1, const char *str2, size_t num)
{
    return strncmp(str1, str2, num);
}
