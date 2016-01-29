#include <UnitTest++.h>
#include "fslc_string.h"
#include "stringx.h"
#include <string.h>

/** Test fixture containing 2 identically pre-seeded memory regions.
 * 
 *  One of them should be modified by tested function - fslc_memset(),
 *  another - by reference implementation - host system's memset().
 * 
 *  Modified regions should be compared afterwards.
 */
struct MemsetFixture
{
    static const int TESTARRAY_SIZE = 24;
    
    char testArray[TESTARRAY_SIZE];
    char expected[TESTARRAY_SIZE];
    
    MemsetFixture() 
    {
        for (int i = 0; i < TESTARRAY_SIZE; ++i)
        {
            testArray[i] = i+'A';
            expected[i] = testArray[i];
        }
    }
};


SUITE(MemSet)
{
    TEST_FIXTURE(MemsetFixture, SetZeroAligned8Bytes)
    {
        void *r = fslc_memset(testArray+8, 0, 8);
        memset(expected+8, 0, 8);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+8, r);
    }
    
    TEST_FIXTURE(MemsetFixture, SetZeroOffset1Negative8Bytes)
    {
        void *r = fslc_memset(testArray+7, 0, 8);
        memset(expected+7, 0, 8);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+7, r);
    }
    
    TEST_FIXTURE(MemsetFixture, SetZeroOffset1Positive8Bytes)
    {
        void *r = fslc_memset(testArray+9, 0, 8);
        memset(expected+9, 0, 8);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+9, r);
    }
    
    TEST_FIXTURE(MemsetFixture, SetZeroOffset1Both10Bytes)
    {        
        void *r = fslc_memset(testArray+7, 0, 10);
        memset(expected+7, 0, 10);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+7, r);
    }

    TEST_FIXTURE(MemsetFixture, SetZeroOffset1Both6Bytes)
    {
        void *r = fslc_memset(testArray+9, 0, 6);
        memset(expected+9, 0, 6);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+9, r);
    }
    
    TEST_FIXTURE(MemsetFixture, Set42Aligned8Bytes)
    {
        void *r = fslc_memset(testArray+8, 42, 8);
        memset(expected+8, 42, 8);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+8, r);
    }
    
    TEST_FIXTURE(MemsetFixture, SetMultiByteAligned8Bytes)
    {
        void *r = fslc_memset(testArray+8, 0x4266, 8);
        memset(expected+8, 0x4266, 8);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+8, r);
    }
    
    TEST_FIXTURE(MemsetFixture, SetMultiByteOffset1Both10Bytes)
    {        
        void *r = fslc_memset(testArray+7, 0x4266, 10);
        memset(expected+7, 0x4266, 10);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+7, r);
    }

    TEST_FIXTURE(MemsetFixture, SetLDiffBytes)
    {
        #if __SIZEOF_LONG__ == 4
            unsigned long val = 0xCAFEBABE;
            unsigned char setVal[] = { 0xCA, 0xBE, 0xBA, 0xFE, 0xCA, 0xBE, 0xBA, 0xFE, 0xCA, 0xBE, 0xBA, 0xFE, 0xCA, 0xBE, 0xBA, 0xFE };
        #elif __SIZEOF_LONG__ == 8
            unsigned long val = 0xDEADBEEFCAFEBABE;
            unsigned char setVal[] = { 0xCA, 0xEF, 0xBE, 0xAD, 0xDE, 0xBE, 0xBA, 0xFE, 0xCA, 0xEF, 0xBE, 0xAD, 0xDE, 0xBE, 0xBA, 0xFE };
        #endif

        void *r = fslc_memset_l(testArray+3, val, 16);
        memcpy(expected+3, setVal, 16);

        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
    }
}
