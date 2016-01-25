#ifndef FSLC_STRINGX_H
#define FSLC_STRINGX_H

#include <stddef.h>

#ifndef ALT_FSLC_NAMES

#define fslc_memset_l     memset_l
#define fslc_strcpy_e   strcpy_e
#define fslc_strncpy_e  strncpy_e

#endif /* ALT_FSLC_NAMES */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    void *fslc_memset_l(void *ptr, unsigned long value, size_t num);
    char *fslc_strcpy_e(char *dest, const char *src);
    char *fslc_strncpy_e(char *dest, const char *src, size_t len);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FSLC_STRINGX_H */
