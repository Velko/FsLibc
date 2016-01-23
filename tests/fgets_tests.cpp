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

    TEST_FIXTURE(StdIOFixture, FGetsCrLfLineTest)
    {
        istring.str("Hello\r\nWorld");

        char text_read[20];

        char *str = fslc_fgets(text_read, 20, &stream);

        CHECK_EQUAL(text_read, str);
        CHECK_EQUAL(0, str[7]);
        CHECK_EQUAL(7, strlen(str));
        CHECK_EQUAL("Hello\r\n", std::string(str));
    }

    TEST_FIXTURE(StdIOFixture, FGetsAfterNewLineTest)
    {
        istring.str("Hello\nWorld");

        char text_read[20];

        fslc_fgets(text_read, 20, &stream);
        char *str = fslc_fgets(text_read, 20, &stream);


        CHECK_EQUAL(text_read, str);
        CHECK_EQUAL(0, str[5]);
        CHECK_EQUAL(5, strlen(str));
        CHECK_EQUAL("World", std::string(str));
    }

    TEST_FIXTURE(StdIOFixture, FGetsAfterCrLfLineTest)
    {
        istring.str("Hello\r\nWorld");

        char text_read[20];

        fslc_fgets(text_read, 20, &stream);
        char *str = fslc_fgets(text_read, 20, &stream);

        CHECK_EQUAL(text_read, str);
        CHECK_EQUAL(0, str[5]);
        CHECK_EQUAL(5, strlen(str));
        CHECK_EQUAL("World", std::string(str));
    }
}
