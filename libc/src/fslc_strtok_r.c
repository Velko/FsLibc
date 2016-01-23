#include "fslc_string.h"
#include <string.h>

char *fslc_strtok_r(char *str, const char *delim, char **save_p)
{
    return strtok_r(str, delim, save_p);
}
