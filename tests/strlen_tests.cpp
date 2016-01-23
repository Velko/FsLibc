#include <UnitTest++.h>
#define ALT_FSLC_NAMES /* use alternative FSLC names - do not clash with Host Libc */
#include "fslc_string.h"
#include <string.h>

SUITE(StrLen)
{
    TEST(BasicTest)
    {
        const char *txt = "Test string";
        
        int r = fslc_strlen(txt);
        int e = strlen(txt);

        CHECK_EQUAL(e, r);
    }
}
