#ifndef FSLC_MALLOC_H
#define FSLC_MALLOC_H

/* This header file contains internal implementation details of FsLibc Malloc. In order to *use* malloc()
 * one should include usual stdlib.h header file.
 */

#include <stddef.h>

struct chunk_header_t
{
    size_t size_x;
};

struct free_header_t
{
    size_t size_x;
    struct free_header_t *up;
    struct free_header_t *down;
};

struct bin_t
{
    size_t size;
};

#define MALLOC_BIN_COUNT    128
#define CHUNK_MIN_SIZE      (sizeof(struct free_header_t) + sizeof(struct chunk_header_t))

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FSLC_MALLOC_H */
