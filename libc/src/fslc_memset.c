#include "fslc_string.h"
#include "fslc_stringx.h"
#include <stdint.h>

void *fslc_memset(void *ptr, int value, size_t num)
{
    /* Will use memset_l() to actually fill the memory region. If value is non-zero, we need
     * to replicate lowest byte to all the long's bytes.
     */
    if (value)
    {
        unsigned char c_val = value;
        unsigned long l_val = (c_val << 0) | (c_val << 8) | (c_val << 16) | (c_val << 24);

        #if __SIZEOF_LONG__ == 8
        l_val |= l_val << 32;
        #endif

        return fslc_memset_l(ptr, l_val, num);
    }
    else
        return fslc_memset_l(ptr, value, num);
}

void *fslc_memset_l(void *ptr, unsigned long value, size_t num)
{
    unsigned char *b_src = (unsigned char *)&value;
    unsigned char *b_dst = (unsigned char *)ptr;

    /* Byte by byte - to aligned word address */
    b_src += ((uintptr_t)b_dst & (sizeof(unsigned long)-1));
    for (;((uintptr_t)b_dst & (sizeof(unsigned long)-1)) && num > 0; b_dst++,b_src++,num--)
    {
        *b_dst = *b_src;
    }

    /* All aligned */
    unsigned long *w_dst = (unsigned long *)b_dst;
    for (;num >= sizeof(unsigned long); w_dst++,num -= sizeof(unsigned long))
    {
        *w_dst= value;
    }

    /* Unaligned ending */
    b_src = (unsigned char *)&value;
    b_dst = (unsigned char *)w_dst;
    for (; num > 0; b_dst++,b_src++,num--)
    {
        *b_dst = *b_src;
    }
    return ptr;
}
