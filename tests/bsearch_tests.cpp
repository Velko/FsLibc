#include <UnitTest++.h>
#include "fslc_stdlib.h"


static void *high_range;
static void *low_range;
static void *key_ptr;

static int cmp_intp(const void *lhs, const void *rhs)
{
    CHECK((lhs >= low_range && lhs < high_range) || lhs == key_ptr);
    CHECK((rhs >= low_range && rhs < high_range) || rhs == key_ptr);

    return *((int*)lhs) - *((int*)rhs);
}

SUITE(BSearch)
{
    TEST(FindItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 30;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK_EQUAL(arr + 2, found);
    }

    TEST(FindItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 30;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK_EQUAL(arr + 2, found);
    }

    TEST(FindLargestItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 80;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK_EQUAL(arr + 7, found);
    }

    TEST(FindLargestItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 90;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK_EQUAL(arr + 8, found);
    }

    TEST(FindSmallestItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 10;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK_EQUAL(arr, found);
    }

    TEST(FindSmallestItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 10;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK_EQUAL(arr, found);
    }

    TEST(NotFindLargestItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 90;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK(found == nullptr);
    }

    TEST(NotFindLargestItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 100;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK(found == nullptr);
    }

    TEST(NotFindSmallestItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 0;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK(found == nullptr);
    }

    TEST(NotFindSmallestItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 0;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK(found == nullptr);
    }

    TEST(NotFindItemEven)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

        int key = 65;

        low_range = arr;
        high_range = arr + 8;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 8, sizeof(int), cmp_intp);

        CHECK(found == nullptr);
    }

    TEST(NotFindItemOdd)
    {
        int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };

        int key = 25;

        low_range = arr;
        high_range = arr + 9;
        key_ptr = &key;

        int *found = (int *)fslc_bsearch(&key, arr, 9, sizeof(int), cmp_intp);

        CHECK(found == nullptr);
    }
}
