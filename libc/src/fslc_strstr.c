#include "fslc_string.h"
#include <string.h>

char *fslc_strstr(const char *search_in, const char *search_for)
{
    return strstr(search_in, search_for);
}
