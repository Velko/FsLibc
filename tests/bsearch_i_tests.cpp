#include <UnitTest++.h>
#include "stdlibx.h"


static void *high_range;
static void *low_range;
static void *key_ptr;

static int cmp_intp(const void *lhs, const void *rhs)
{
    CHECK((lhs >= low_range && lhs < high_range) || lhs == key_ptr);
    CHECK((rhs >= low_range && rhs < high_range) || rhs == key_ptr);

    return *((int*)lhs) - *((int*)rhs);
}

SUITE(BSearchI)
{
    TEST(FindItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 30;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK_EQUAL(2, found);
    }
    
     TEST(FindItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 30;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK_EQUAL(2, found);
    }

    TEST(FindLargestItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 80;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK_EQUAL(7, found);
    }

    TEST(FindLargestItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 90;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK_EQUAL(8, found);
    }

    TEST(FindSmallestItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 10;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK_EQUAL(0, found);
    }

    TEST(FindSmallestItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 10;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK_EQUAL(0, found);
    }
    
    TEST(NotFindSmallestItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 0;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK_EQUAL(~0, found);
    }

    TEST(NotFindSmallestItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 0;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK_EQUAL(~0, found);
    }

    TEST(NotFindItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 65;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK_EQUAL(~6, found);
    }

    TEST(NotFindItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 25;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK_EQUAL(~2, found);
    }

    TEST(NotFindLargestItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 90;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK_EQUAL(~8, found);
    }

    TEST(NotFindLargestItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 95;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int found = fslc_bsearch_i(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK_EQUAL(~9, found);
    }
}