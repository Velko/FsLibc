#include <UnitTest++.h>

#include "stdio_fixture.h"
#include <string.h>

SUITE(FGets)
{
    TEST_FIXTURE(StdIOFixture, FGetsToEofTest)
    {
        istring.str("Hello");
        
        char text_read[10];
        
        char *str = fslc_fgets(text_read, 10, &stream);
        
        CHECK_EQUAL(text_read, str);
        CHECK_EQUAL(0, str[5]);
        CHECK_EQUAL(5, strlen(str));
        CHECK_EQUAL("Hello", std::string(str));
    }
    
    TEST_FIXTURE(StdIOFixture, FGetsNewLineTest)
    {
        istring.str("Hello\nWorld");
        
        char text_read[20];
        
        char *str = fslc_fgets(text_read, 20, &stream);
        
        CHECK_EQUAL(text_read, str);
        CHECK_EQUAL(0, str[6]);
        CHECK_EQUAL(6, strlen(str));
        CHECK_EQUAL("Hello\n", std::string(str));
    }
    
    TEST_FIXTURE(StdIOFixture, FGetsBufSizeTest)
    {
        istring.str("Hello World");
        
        char text_read[20];
        
        char *str = fslc_fgets(text_read, 5, &stream);
        
        CHECK_EQUAL(text_read, str);
        CHECK_EQUAL(0, str[5]);
        CHECK_EQUAL(5, strlen(str));
        CHECK_EQUAL("Hello", std::string(str));
    }
}
