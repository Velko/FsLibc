#include <UnitTest++.h>
#include "fslc_string.h"
#include <string.h>

#include "misc_utils.h"

SUITE(MemCmp)
{
    TEST(CmpAligned8BytesEqual)
    {
        char arr1[] = "12345678";
        char arr2[] = "12345678";

        int cmp_res = fslc_memcmp(arr1, arr2, 8);
        int cmp_exp = memcmp(arr1, arr2, 8);

        CHECK_EQUAL(SIGNOF(cmp_exp), SIGNOF(cmp_res));
    }
    
    TEST(CmpAligned8BytesGt)
    {
        char arr1[] = "12345678";
        char arr2[] = "12335678";

        int cmp_res = fslc_memcmp(arr1, arr2, 8);
        int cmp_exp = memcmp(arr1, arr2, 8);

        CHECK_EQUAL(SIGNOF(cmp_exp), SIGNOF(cmp_res));
    }
    
    TEST(CmpUnAlignedBeginning19BytesLt)
    {
        char arr1[] = "12335678901234567890";
        char arr2[] = "12345678901234567890";

        int cmp_res = fslc_memcmp(arr1+1, arr2+1, 19);
        int cmp_exp = memcmp(arr1+1, arr2+1, 19);

        CHECK_EQUAL(SIGNOF(cmp_exp), SIGNOF(cmp_res));
    }

    TEST(CmpUnAlignedBeginning2BytesEq)
    {
        char arr1[] = "123";
        char arr2[] = "123";

        int cmp_res = fslc_memcmp(arr1+1, arr2+1, 2);
        int cmp_exp = memcmp(arr1+1, arr2+1, 2);
        
        CHECK_EQUAL(SIGNOF(cmp_exp), SIGNOF(cmp_res));
    }

    TEST(CmpUnAlignedEnd19BytesLt)
    {
        char arr1[] = "12345678901234567790";
        char arr2[] = "12345678901234567890";

        int cmp_res = fslc_memcmp(arr1+1, arr2+1, 19);
        int cmp_exp = memcmp(arr1+1, arr2+1, 19);
        
        CHECK_EQUAL(SIGNOF(cmp_exp), SIGNOF(cmp_res));
    }

    TEST(CmpUnAlignedEnd19BytesGt)
    {
        char arr1[] = "12345678901234567990";
        char arr2[] = "12345678901234567890";

        int cmp_res = fslc_memcmp(arr1+1, arr2+1, 19);
        int cmp_exp = memcmp(arr1+1, arr2+1, 19);

        CHECK_EQUAL(SIGNOF(cmp_exp), SIGNOF(cmp_res));
    }

    TEST(CmpLongLongNegAlignedGt)
    {
        unsigned long long arr1[] = {0xBADABAFAEACEBCDFULL};
        unsigned long long arr2[] = {0x0000000000000000ULL};

        int cmp_res = fslc_memcmp(arr1, arr2, sizeof(arr1));
        int cmp_exp = memcmp(arr1, arr2, sizeof(arr1));
        CHECK_EQUAL(SIGNOF(cmp_exp), SIGNOF(cmp_res));
    }

    TEST(CmpLongLongNegUnAlignedGt)
    {
        unsigned long long arr1[] = {0xBADABAFAEACEBCDFULL};
        unsigned long long arr2[] = {0x0000000000000000ULL};

        int cmp_res = fslc_memcmp((void *)(((uintptr_t)arr1)+1), (void *)(((uintptr_t)arr2)+1), sizeof(arr1)-1);
        int cmp_exp = memcmp((void *)(((uintptr_t)arr1)+1), (void *)(((uintptr_t)arr2)+1), sizeof(arr1)-1);
        CHECK_EQUAL(SIGNOF(cmp_exp), SIGNOF(cmp_res));
    }

    TEST(CmpLongLongNegAlignedLt)
    {
        unsigned long long arr1[] = {0x0000000000000000ULL};
        unsigned long long arr2[] = {0xBADABAFAEACEBCDFULL};

        int cmp_res = fslc_memcmp(arr1, arr2, sizeof(arr1));
        int cmp_exp = memcmp(arr1, arr2, sizeof(arr1));
        CHECK_EQUAL(SIGNOF(cmp_exp), SIGNOF(cmp_res));
    }

    TEST(CmpLongLongNegUnAlignedLt)
    {
        unsigned long long arr1[] = {0x0000000000000000ULL};
        unsigned long long arr2[] = {0xBADABAFAEACEBCDFULL};

        int cmp_res = fslc_memcmp((void *)(((uintptr_t)arr1)+1), (void *)(((uintptr_t)arr2)+1), sizeof(arr1)-1);
        int cmp_exp = memcmp((void *)(((uintptr_t)arr1)+1), (void *)(((uintptr_t)arr2)+1), sizeof(arr1)-1);
        CHECK_EQUAL(SIGNOF(cmp_exp), SIGNOF(cmp_res));
    }
}
