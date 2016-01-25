#include <UnitTest++.h>
#include "fslc_string.h"
#include <string.h>

SUITE(StrSpn)
{
    TEST(BeginningTest)
    {
        const char *txt = "*^*#^*The text continues";

        size_t r = fslc_strspn(txt, "#*^");
        size_t e = strspn(txt, "#*^");

        CHECK_EQUAL(e, r);
    }

    TEST(ZeroResTest)
    {
        const char *txt = "This is *^*#^*";

        size_t r = fslc_strspn(txt, "#*^");
        size_t e = strspn(txt, "#*^");

        CHECK_EQUAL(e, r);
    }

    TEST(AllTest)
    {
        const char *txt = "*^*#^*^^**###";

        size_t r = fslc_strspn(txt, "#*^");
        size_t e = strspn(txt, "#*^");

        CHECK_EQUAL(e, r);
    }
}
