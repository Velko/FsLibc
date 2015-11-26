#ifndef FSLC_STRING_H
#define FSLC_STRING_H

#include <stddef.h>

#ifndef ALT_FSLC_NAMES
#define fslc_memset     memset
#define fslc_memcpy     memcpy
#define fslc_memmove    memmove
#endif /* ALT_FSLC_NAMES */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    void *fslc_memset(void *ptr, int value, size_t num);
    void *fslc_memcpy(void *dest, const void *src, size_t len);
    void *fslc_memmove(void *dest, const void *src, size_t len);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


#endif /* FSLC_STRING_H */
