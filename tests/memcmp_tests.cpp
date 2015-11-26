#include <UnitTest++.h>
#define ALT_FSLC_NAMES /* use alternative FSLC names - do not clash with Host Libc */
#include "fslc_string.h"
#include <string.h>

SUITE(MemCmp)
{
    TEST(CmpAligned8BytesEqual)
    {
        char arr1[] = "12345678";
        char arr2[] = "12345678";
        
        int cmp_res = fslc_memcmp(arr1, arr2, 8);
        
        CHECK_EQUAL(0, cmp_res);
    }
    
    TEST(CmpAligned8BytesGt)
    {
        char arr1[] = "12345678";
        char arr2[] = "12335678";
        
        int cmp_res = fslc_memcmp(arr1, arr2, 8);
        
        CHECK(cmp_res>0);
    }
    
    TEST(CmpAligned8BytesLt)
    {
        char arr1[] = "12335678";
        char arr2[] = "12345678";
        
        int cmp_res = fslc_memcmp(arr1, arr2, 8);
        
        CHECK(cmp_res<0);
    }
}
