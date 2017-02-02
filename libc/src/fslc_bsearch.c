#include "fslc_stdlib.h"

void *fslc_bsearch(const void *key, const void *base, size_t num, size_t size, int (*cmp_proc)(const void *, const void *))
{
    size_t low = 0;
    size_t high = num;
    size_t middle;
    char *cbase = (char *)base;
    char *ptr;
    int cmp;

    while (low < high)
    {
        middle = (low + high) >> 1;
        ptr = cbase + (middle * size);
        cmp = cmp_proc(key, ptr);
        if (cmp > 0)
        {
            low = middle + 1;
        }
        else if (cmp < 0)
        {
            high = middle;
        }
        else
            return ptr;
    }

    return NULL;
}
