#ifndef FSLC_STRING_H
#define FSLC_STRING_H

#include <stddef.h>

#ifndef ALT_FSLC_NAMES
#define fslc_memset     memset
#endif /* ALT_FSLC_NAMES */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    void *fslc_memset(void *ptr, int value, size_t num);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


#endif /* FSLC_STRING_H */
