#include <UnitTest++.h>
#include "fslc_string.h"
#include <string.h>

/** Test fixture containing pre-seeded memory regions.
 * 
 *  sourceArray - source memory should be copied from,
 *  testArray - should be modified by tested function - fslc_memcpy(),
 *  expected - by reference implementation - host system's memcpy().
 * 
 *  Modified regions should be compared afterwards.
 */
struct MemcpyFixture
{
    static const int TESTARRAY_SIZE = 24;
    
    char sourceArray[TESTARRAY_SIZE];
    char testArray[TESTARRAY_SIZE];
    char expected[TESTARRAY_SIZE];
    
    MemcpyFixture()
    {
        for (int i = 0; i < TESTARRAY_SIZE; ++i)
        {
            sourceArray[i] = i+'a'; 
            testArray[i] = i+'A';
            expected[i] = testArray[i];
        }
    }
};

SUITE(MemCpy)
{
    TEST_FIXTURE(MemcpyFixture, CopyAligned8Bytes)
    {
        void *r = fslc_memcpy(testArray+8, sourceArray+8, 8);
        memcpy(expected+8, sourceArray+8, 8);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+8, r);
    }
    
    TEST_FIXTURE(MemcpyFixture, CopyOffset1Negative8Bytes)
    {
        void *r = fslc_memcpy(testArray+7, sourceArray+7, 8);
        memcpy(expected+7, sourceArray+7, 8);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+7, r);
    }
    
    TEST_FIXTURE(MemcpyFixture, CopyOffset1Positive8Bytes)
    {
        void *r = fslc_memcpy(testArray+9, sourceArray+9, 8);
        memcpy(expected+9, sourceArray+9, 8);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+9, r);
    }
    
    TEST_FIXTURE(MemcpyFixture, CopyOffset1Both10Bytes)
    {        
        void *r = fslc_memcpy(testArray+7, sourceArray+7, 10);
        memcpy(expected+7, sourceArray+7, 10);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+7, r);
    }

    TEST_FIXTURE(MemcpyFixture, CopyOffset1Both6Bytes)
    {
        void *r = fslc_memcpy(testArray+9, sourceArray+9, 6);
        memcpy(expected+9, sourceArray+9, 6);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+9, r);
    }
    
    TEST_FIXTURE(MemcpyFixture, CopyOffset2and1Negative8Bytes)
    {
        void *r = fslc_memcpy(testArray+6, sourceArray+7, 8);
        memcpy(expected+6, sourceArray+7, 8);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+6, r);
    }
    
    TEST_FIXTURE(MemcpyFixture, CopyOffset2and1Positive8Bytes)
    {
        void *r = fslc_memcpy(testArray+10, sourceArray+9, 8);
        memcpy(expected+10, sourceArray+9, 8);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+10, r);
    }
    
    TEST_FIXTURE(MemcpyFixture, CopyOffset2and1Both10Bytes)
    {        
        void *r = fslc_memcpy(testArray+6, sourceArray+7, 10);
        memcpy(expected+6, sourceArray+7, 10);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+6, r);
    }

    TEST_FIXTURE(MemcpyFixture, CopyOffset2and1Both6Bytes)
    {
        void *r = fslc_memcpy(testArray+10, sourceArray+9, 6);
        memcpy(expected+10, sourceArray+9, 6);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+10, r);
    }

	TEST_FIXTURE(MemcpyFixture, CopyOffset2and1Both1Byte)
    {
        void *r = fslc_memcpy(testArray+10, sourceArray+9, 1);
        memcpy(expected+10, sourceArray+9, 1);

        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+10, r);
    }
}
