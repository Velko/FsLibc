#include "fslc_string.h"

char* fslc_strrstr(const char* search_in, const char* search_for)
{
    size_t len_in = fslc_strlen(search_in);
    size_t len_for = fslc_strlen(search_for);

    if (len_for > len_in)
        return NULL;

    if (len_for == 0)
        return (char*)search_in + len_in;

    for (const char* current = search_in + len_in - len_for; current >= search_in; current--)
    {
        const char* ptr1 = current;
        const char* ptr2 = search_for;

        // Check if search_for matches starting from current position
        while (*ptr1 != '\0' && *ptr2 != '\0' && *ptr1 == *ptr2)
        {
            ptr1++;
            ptr2++;
        }

        if (*ptr2 != '\0') 
            continue;

        // Found a match

        return (char*)current;
    }

    return NULL;
}