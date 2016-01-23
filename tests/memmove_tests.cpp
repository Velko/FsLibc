#include <UnitTest++.h>
#define ALT_FSLC_NAMES /* use alternative FSLC names - do not clash with Host Libc */
#include "fslc_string.h"
#include <string.h>

/** Test fixture containing pre-seeded memory regions.
 * 
 *  testArray - should be modified by tested function - fslc_memmove(),
 *  expected - by reference implementation - host system's memmove().
 * 
 *  Modified regions should be compared afterwards.
 */
struct MemmoveFixture
{
    static const int TESTARRAY_SIZE = 48;
    
    char testArray[TESTARRAY_SIZE];
    char expected[TESTARRAY_SIZE];
    
    MemmoveFixture()
    {
        for (int i = 0; i < TESTARRAY_SIZE; ++i)
        {
            testArray[i] = i+'A';
            expected[i] = testArray[i];
        }
    }
};

SUITE(MemMove)
{
    TEST_FIXTURE(MemmoveFixture, MoveAligned8BytesNonOverlap)
    {
        void *r = fslc_memmove(testArray+24, testArray+8, 16);
        memmove(expected+24, expected+8, 16);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+24, r);
    }
    
    TEST_FIXTURE(MemmoveFixture, MoveAligned16BytesOverlapForward)
    {
        void *r = fslc_memmove(testArray+16, testArray+8, 16);
        memmove(expected+16, expected+8, 16);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+16, r);
    }
    
    TEST_FIXTURE(MemmoveFixture, MoveAligned16BytesOverlapBackward)
    {
        void *r = fslc_memmove(testArray+8, testArray+16, 16);
        memmove(expected+8, expected+16, 16);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+8, r);
    }
    
    
    TEST_FIXTURE(MemmoveFixture, MoveNonAligned13BytesNonOverlap)
    {
        void *r = fslc_memmove(testArray+22, testArray+7, 13);
        memmove(expected+22, expected+7, 13);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+22, r);
    }
    
    TEST_FIXTURE(MemmoveFixture, MoveNonAligned19BytesOverlapForward)
    {
        void *r = fslc_memmove(testArray+14, testArray+6, 19);
        memmove(expected+14, expected+6, 19);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+14, r);
    }
    
    TEST_FIXTURE(MemmoveFixture, MoveNonAligned19BytesOverlapBackward)
    {
        void *r = fslc_memmove(testArray+6, testArray+14, 19);
        memmove(expected+6, expected+14, 19);
        
        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+6, r);
    }

    TEST_FIXTURE(MemmoveFixture, MoveNonAligned1ByteNonOverlap)
    {
        void *r = fslc_memmove(testArray+22, testArray+7, 1);
        memmove(expected+22, expected+7, 1);

        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+22, r);
    }

    TEST_FIXTURE(MemmoveFixture, MoveNonAligned2BytesOverlapBackward)
    {
        void *r = fslc_memmove(testArray+9, testArray+8, 2);
        memmove(expected+9, expected+8, 2);

        CHECK_ARRAY_EQUAL(expected, testArray, TESTARRAY_SIZE);
        CHECK_EQUAL(testArray+9, r);
    }
}
