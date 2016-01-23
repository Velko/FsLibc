#include "strmod_fixture.h"
#include <string.h>

StrModFixture::StrModFixture()
{
    memset(testString, 0xFF, sizeof(testString));
    memset(expectedString, 0xFF, sizeof(testString));
}

