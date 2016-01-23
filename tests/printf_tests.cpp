#include <UnitTest++.h>

#include "stdio_fixture.h"

SUITE(PrintF)
{
    TEST_FIXTURE(StdIOFixture, BasicPrintFTest)
    {
        int r = fslc_fprintf(&stream, "Hello, World!\n");
        
        CHECK_EQUAL("Hello, World!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFStringTest)
    {
        int r = fslc_fprintf(&stream, "Hello from %s!\n", "PrintF");
        
        CHECK_EQUAL("Hello from PrintF!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintF2StringsTest)
    {
        int r = fslc_fprintf(&stream, "%s from %s!\n", "Hello", "PrintF");
        
        CHECK_EQUAL("Hello from PrintF!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFCharTest)
    {
        int r = fslc_fprintf(&stream, "Hello, %corld!\n", 'W');
        
        CHECK_EQUAL("Hello, World!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFPercentTest)
    {
        int r = fslc_fprintf(&stream, "Special offer: 50%% off!");
        
        CHECK_EQUAL("Special offer: 50% off!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFPrePostMultiTest)
    {
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        int r = fslc_fprintf(&stream, "Testing %s%% of all possibilities%c", "a few ", '!');
        
        int e = eprintf("Testing %s%% of all possibilities%c", "a few ", '!');

        const char *expected_str = expected_fstring.get();
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        for (const char *c = expected_str; *c; ++c)
            expected_calls.push_back({ CalledFunc::PutC, *c });
        expected_calls.push_back({ CalledFunc::PostOp, 0 });

        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
        
        CHECK_EQUAL(expected_str, ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFPrePostMultiEofTest)
    {
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        eof_counter = 20;
        
        int r = fslc_fprintf(&stream, "Testing %s%% of all possibilities%c", "a few ", '!');
        
        const char *expected_str = "Testing a few % of a";
        //                          12345678901234567890
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        for (const char *c = expected_str; *c; ++c)
            expected_calls.push_back({ CalledFunc::PutC, *c });
        expected_calls.push_back({ CalledFunc::PutC, 'l' }); // EOF
        expected_calls.push_back({ CalledFunc::PostOp, 0 });

        CHECK(r < 0);
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
        
        CHECK_EQUAL(expected_str, ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFBasicIntTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %d!", 42);
        
        CHECK(r >= 0);
        CHECK_EQUAL("The answer is 42!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFZeroIntTest)
    {
        int r = fslc_fprintf(&stream, "Zero is %d!", 0);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Zero is 0!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFNegativeTest)
    {
        int r = fslc_fprintf(&stream, "Less than zero: %d!", -54);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Less than zero: -54!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUIntMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max uint is %u\n", -1);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Max uint is 4294967295\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFBasicHexTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %x!", 0x74df);
        
        CHECK(r >= 0);
        CHECK_EQUAL("The answer is 74df!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFBasicUpperHexTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %X!", 0x74df);
        
        CHECK(r >= 0);
        CHECK_EQUAL("The answer is 74DF!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFZeroHexTest)
    {
        int r = fslc_fprintf(&stream, "Zero is %x!", 0);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Zero is 0!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUHExMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max hex is %x\n", -1);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Max hex is ffffffff\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFLongIntTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %ld!", 435434432L);
        
        int e = eprintf("The answer is %ld!", 435434432L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFLongNegativeTest)
    {
        int r = fslc_fprintf(&stream, "Less than zero: %ld!", -57299223L);
        
        int e = eprintf("Less than zero: %ld!", -57299223L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFULongMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max ulong is %lu\n", -1L);
        
        int e = eprintf("Max ulong is %lu\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFULongHexMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max long hex is %lx\n", -1L);
        
        int e = eprintf("Max long hex is %lx\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFULongHexUpperMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max long hex is %lX\n", -1L);
        
        int e = eprintf("Max long hex is %lX\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFVeryLongIntTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %lld!", 435432343442444432LL);
        
        int e = eprintf("The answer is %lld!", 435432343442444432LL);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFVeryLongNegativeTest)
    {
        int r = fslc_fprintf(&stream, "Less than zero: %lld!", -5729932434424223L);
        
        int e = eprintf("Less than zero: %lld!", -5729932434424223L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUVeryLongMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max ulonglong is %llu\n", -1L);
        
        int e = eprintf("Max ulonglong is %llu\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFVeryLongZeroTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %lld!", 0LL);
        
        int e = eprintf("The answer is %lld!", 0LL);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUVeryLongHexDigitsTest)
    {
        int r = fslc_fprintf(&stream, "Long long hex %llx\n", 0xDEADBEEFCAFE0000LL);
        
        int e = eprintf("Long long hex %llx\n", 0xDEADBEEFCAFE0000LL);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUVeryLongHexZeroTest)
    {
        int r = fslc_fprintf(&stream, "Long long hex zero %llx\n", 0LL);
        
        int e = eprintf("Long long hex zero %llx\n", 0LL);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUVeryLongHexMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max long long hex is %llx\n", -1L);
        
        int e = eprintf("Max long long hex is %llx\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUVeryLongUpperHexMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max long long hex is %llX\n", -1L);
        
        int e = eprintf("Max long long hex is %llX\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFIntSignEofTest)
    {
        eof_counter = 10;
        int r = fslc_fprintf(&stream, "Will stop %d", -1223);
        
        int e = eprintf("Will stop ");
        
        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFIntMiddleEofTest)
    {
        eof_counter = 12;
        int r = fslc_fprintf(&stream, "Will stop %d", -1223);
        
        int e = eprintf("Will stop -1");
        
        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFVeryLongSignEofTest)
    {
        eof_counter = 10;
        int r = fslc_fprintf(&stream, "Will stop %lld", -1223LL);
        
        int e = eprintf("Will stop ");
        
        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFVeryLongMiddleEofTest)
    {
        eof_counter = 12;
        int r = fslc_fprintf(&stream, "Will stop %lld", -1223LL);
        
        int e = eprintf("Will stop -1");
        
        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFStringMiddleEofTest)
    {
        eof_counter = 12;
        int r = fslc_fprintf(&stream, "Will stop %s", "1223");
        
        int e = eprintf("Will stop 12");
        
        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFCharEofTest)
    {
        eof_counter = 10;
        int r = fslc_fprintf(&stream, "Will stop %c", 'a');
        
        int e = eprintf("Will stop ");
        
        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFPercentEofTest)
    {
        eof_counter = 10;
        int r = fslc_fprintf(&stream, "Will stop %%");
        
        int e = eprintf("Will stop ");
        
        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUIntMiddleEofTest)
    {
        eof_counter = 12;
        int r = fslc_fprintf(&stream, "Will stop %u", 1223);
        
        int e = eprintf("Will stop 12");
        
        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUHexMiddleEofTest)
    {
        eof_counter = 12;
        int r = fslc_fprintf(&stream, "Will stop %x", 0xA223);
        
        int e = eprintf("Will stop a2");
        
        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUHEXMiddleEofTest)
    {
        eof_counter = 12;
        int r = fslc_fprintf(&stream, "Will stop %X", 0xA223);
        
        int e = eprintf("Will stop A2");
        
        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }

    TEST_FIXTURE(StdIOFixture, PrintPPointerTest)
    {
        void *ptr = (void *)0x032D47F2;

        int r = fslc_fprintf(&stream, "A pointer: %p!", ptr);

        int e = eprintf("A pointer: %p!", ptr);

        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }

    TEST_FIXTURE(StdIOFixture, PrintPPointerEofPrefixTest)
    {
        void *ptr = (void *)0x032D47F2;

        int e = eprintf("A pointer: 0");

        eof_counter = e;

        int r = fslc_fprintf(&stream, "A pointer: %p!", ptr);

        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }

    TEST_FIXTURE(StdIOFixture, PrintPPointerEofMiddleTest)
    {
        void *ptr = (void *)0x032D47F2;

        int e = eprintf("A pointer: 0x32");

        eof_counter = e;

        int r = fslc_fprintf(&stream, "A pointer: %p!", ptr);

        CHECK(r < 0);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFInvalidTest)
    {
        // How to handle invalid printf format strings is undefined.
        // But we should check anyway - just in case.
        int r = fslc_fprintf(&stream, "An invalid %k specifier");

        CHECK(r >= 0);
        CHECK_EQUAL("An invalid  specifier", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFStdoutNDefaultTest)
    {
        FSLC_FILE null_stream;
        null_stream.pre_output = null_prepostop;
        null_stream.putc = null_putc;
        null_stream.post_output = null_prepostop;
        
        fslc_stdout = &null_stream;
        
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        int r = fslc_fprintf(&stream, "Hello, World!\n");
        int e = eprintf("Hello, World!\n");
        
        const char *expected_str = expected_fstring.get();
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        for (const char *c = expected_str; *c; ++c)
            expected_calls.push_back({ CalledFunc::PutC, *c });
        expected_calls.push_back({ CalledFunc::PostOp, 0 });

        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
        
        CHECK_EQUAL(expected_str, ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }

    TEST_FIXTURE(StdIOFixture, PrintFManyManyArgsTest)
    {
        // On X64_86 first 6 args are passed in registers, rest on the stack. Using va_arg() generates a branch, which
        // is normally not taken by test suite - gives incomplete branch coverage. This test passes many arguments
        // in order to force the second branch to be taken - improve coverage rate.
        int r = fslc_fprintf(&stream, "Arg1: %d, Arg2: %d, Arg3: %d, Arg4: %d, Arg5: %d, Arg6: %u, Arg7: %lld, Arg8: %llu, Arg9: %s", 1, 2, 3, 4, 5, 6U, 17179869184LL, 17179869184LLU, "str");
        int e = eprintf("Arg1: %d, Arg2: %d, Arg3: %d, Arg4: %d, Arg5: %d, Arg6: %u, Arg7: %lld, Arg8: %llu, Arg9: %s", 1, 2, 3, 4, 5, 6U, 17179869184LL, 17179869184LLU, "str");

        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
}
