#ifndef FSLC_MALLOC_H
#define FSLC_MALLOC_H

/* This header file contains internal implementation details of FsLibc Malloc. In order to *use* malloc()
 * one should include usual stdlib.h header file.
 */

#include <stddef.h>


/* Common chunk header.
 * size_x member packs flags, size and associated bin index in 32-bits.
 *
 * It is defined as an array, to allow quick access to preceding
 * chunk's footer (size_x[-1])
 */
struct chunk_header_t
{
    size_t size_x[1];
};

/* Chunk sizes are multiples of at least 16 (4 pointers on 32-bit arch),
 * leaving 4 lowest bits available for flags */
#define CHUNK_FLAGS_MASK        0x0000000F

/* Chunk size occupies 3 bytes and 1 bit, allowing up to 32 MiB chunk size.
 * Currently bins are initialized up to ~18.5 MiB sizes.
 */
#define CHUNK_SIZE_MASK         0x01FFFFF0

/* Chunk bin index. highest 7 bits is just enough to squeeze in index of
 * associated bin.
 */
#define CHUNK_BIN_IDX_MASK      0xFE000000

/* In order to store/retrieve bin index from size_x field, it has to be shifted
 * 3 bytes and one bit.
 */
#define CHUNK_BIN_IDX_SHIFT     25

/* Mask to apply after chunk index has been shifted to retrieve.
 */
#define CHUNK_BIN_IDX_MASK_LO      0x7F

/* Free chunk contains 2 additional pointers */
struct free_header_t
{
    size_t size_x[1];
    struct free_header_t *up;
    struct free_header_t *down;
};

/* Chunk footer should always contain same value as header's size_x[0]. */
struct chunk_footer_t
{
    size_t size_x;
};


struct bin_t
{
    size_t size;
    struct free_header_t *top;
    struct free_header_t *bottom;
};

#define MALLOC_BIN_COUNT    128
#define CHUNK_MIN_SIZE      (sizeof(struct free_header_t) + sizeof(struct chunk_footer_t))
#define ADD_ADDR(targ_type, source, amount)     ((targ_type)(((char *)(source))+(amount)))

#define CHUNK_IDX(size_x)   (((size_x) >> CHUNK_BIN_IDX_SHIFT) & CHUNK_BIN_IDX_MASK_LO)
#define CHUNK_SIZE(size_x)  ((size_x) & CHUNK_SIZE_MASK)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    void initialize_bins(struct bin_t *bins);
    int find_bin_int(struct bin_t *bins, size_t target);
    int find_bin_gte(struct bin_t *bins, size_t target);
    int find_bin_lte(struct bin_t *bins, size_t target);
    void store_chunk(struct bin_t *bin, struct free_header_t *chunk);
    struct free_header_t *pop_chunk(struct bin_t *bin);
    void update_chunk(struct free_header_t *chunk, size_t size, size_t bin_index, unsigned char flags);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FSLC_MALLOC_H */
