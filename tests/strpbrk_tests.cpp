#include <UnitTest++.h>
#define ALT_FSLC_NAMES /* use alternative FSLC names - do not clash with Host Libc */
#include "fslc_string.h"
#include <string.h>

SUITE(StrPBrk)
{
    TEST(BasicTest)
    {
        const char *txt = "Delimited,string;by.some-chars";

        const char *r1 = fslc_strpbrk(txt, ",;.-");
        const char *e1 = fslc_strpbrk(txt, ",;.-");

        CHECK_EQUAL((uintptr_t)e1, (uintptr_t)r1);

        const char *r2 = fslc_strpbrk(r1+1, ",;.-");
        const char *e2 = fslc_strpbrk(e1+1, ",;.-");

        CHECK_EQUAL((uintptr_t)e2, (uintptr_t)r2);

        const char *r3 = fslc_strpbrk(r2+1, ",;.-");
        const char *e3 = fslc_strpbrk(e2+1, ",;.-");

        CHECK_EQUAL((uintptr_t)e3, (uintptr_t)r3);
    }

    TEST(NotFoundTest)
    {
        const char *txt = "Delimited,string;by.some-chars";

        const char *r1 = fslc_strpbrk(txt, "#!$%");
        const char *e1 = fslc_strpbrk(txt, "#!$%");

        CHECK_EQUAL((uintptr_t)e1, (uintptr_t)r1);
    }
}
