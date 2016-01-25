#ifndef STRMOD_FIXTURE_H
#define STRMOD_FIXTURE_H

#define ALT_FSLC_NAMES /* use alternative FSLC names - do not clash with Host Libc */
#include "fslc_string.h"
#include "fslc_stringx.h"


struct StrModFixture
{
    static const int MAXLEN = 100;
    char testString[MAXLEN];
    char expectedString[MAXLEN];

    StrModFixture();
};


#endif /* STRMOD_FIXTURE_H */
