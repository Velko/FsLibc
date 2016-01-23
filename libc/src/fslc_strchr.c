#include "fslc_string.h"
#include <string.h>

char *fslc_strchr(const char *str, int c)
{
    return strchr(str, c);
}
