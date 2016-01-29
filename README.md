Freestanding Libc
=================

Bare-metal programming poses its own challenges. There's no underlying operating system
providing fancy services. No input/output facilities, no even basic helper functions. Only
the code we provide ourselves.

ANSI C Standard calls it *freestanding environment*. [GCC requires][gccstd] the freestanding
environment provide some basic functions: `memcpy()`, `memmove()`, `memset()` and `memcmp()`.
It will assume that these functions are present and use them where it feels like.

[gccstd]: https://gcc.gnu.org/onlinedocs/gcc/Standards.html "Language Standards Supported by GCC"

Of course, somebody has to provide these functions, and that is the main reason why *FsLibc*
exists.

Features
========

Memory manipulation
-------------------

The bare minimum of *required* memory manipulation functions are:

* `memset()` - fill memory with specified byte value;
* `memcpy()` - copy memory from one region to another;
* `memmove()` - copy memory from one region to another, safe for overlapping regions;
* `memcmp()` - compare two memory regions.

As expected, functions are available using include file *string.h*.

Input/Output
------------

Common debugging technique is to print out tracing messages about program's state at various
points, sometimes called *printf debugging*. Obviously, there is no predefined `printf()` available
and we need to provide our own. But it may be very tricky to get output to work, while there
is no output. *FsLibc* provides pre-built I/O facilities, which requires very little to get them
to work. Provided are:

* `putchar()` - put single character on `stdout` stream;
* `fputc()` - put single character on specified stream;
* `puts()` - put a sequence of characters on `stdout` stream;
* `fputs()` - put a sequence of characters on specified stream;
* `printf()` - put formatted output on `stdout` stream, varying number of parameters;
* `fprintf()` - put formatted output on specified stream, varying number of parameters;
* `vprintf()` - put formatted output on `stdout` stream, `va_list` parameter;
* `vfprintf()` - put formatted output on specified stream, `va_list` parameter;
* `fwrite()` - output binary block with specified length;
* `getchar()` - read single character from `stdin` stream;
* `getc()` - read single character from specified stream;
* `fgets()` - read a line of text from specified stream into buffer;
* `ungetc()` - "put back" a single character into input stream;
* `fread()` - read binary block from specified stream into buffer.

There are 2 global variables `stdout` and `stdin` of type `FILE *` provided for usual standard
streams. These, however needs to be set up before use. An example is worth a thousand words:

```C
#include <stdio.h>

static int screen_putc(int c, FILE *stream)
{
    // put character on the screen
}

static int keyboard_getc(FILE *stream)
{
    // read and return a character from keyboard
}

static void screen_pre_output(FILE *stream)
{
    // read cursor position before output
}

static void screen_post_output(FILE *stream)
{
    // set cursor position after output
}

FILE scr_term;

void setup_terminal_io()
{
    // required if output is used
    scr_term.putc = screen_putc;

    // required if input is used
    scr_term.getc = keyboard_getc;

    // optional
    scr_term.pre_output = screen_pre_output;
    scr_term.post_output = screen_post_output;

    // required initial state if input
    // is used
    scr_term.ungetc_buf = -1;

    // pointer to custom data
    scr_term.user_ptr = NULL;

    // initialize needed streams
    stdin = stdout = &scr_term;
}
```

User is required to provide functions that do the actual I/O and
specify them while initializing `FILE` structure. Obviously, if
user does not intend to use input and need no any additional actions
before/after output, the bare minimum is to provide a single function
which puts a single character on the screen, sends it over UART or
signals it some other way (blink a LED in Morse code, if you like).

Input/output functions are available from header file *stdio.h*.

String manipulation
-------------------

Another frequently used class of functions in C standard library is functions for
string manipulation. *FsLibc* provides a number of (by author's opinion) most used
ones:

* `strlen()` - get string length;
* `strcpy()` - copy string;
* `strncpy()` - copy string, limit length;
* `strcmp()` - compare two strings;
* `strncmp()` - compare two strings, limit length;
* `strchr()` - locate first occurrence of character in string;
* `strstr()` - locate substring;
* `strtok_r()` - split string into tokens;
* `strpbrk()` - locate specified characters in string;
* `strspn()` - count specified characters at the beginning of string.

Since there are no external dependencies, no additional setup is required. Functions
are available from header file *string.h*.

Compability
===========

*FsLibc* is intended to be a subset of "normal" C Standard Library. The majority of functions
should behave just like their counterparts from standard library (file a bug, if they do not).

Small exception is *printf* family of functions - they implement only subset of format string
functionality. Only `%s`, `%c`, `%d`, `%i`, `%u`, `%x`, `%X`, `%p` specifiers are supported, no
floating-point support whatsoever. No additional formatting options, with exception of argument
length (`l` and `ll`) are supported. In other words - what works with *FsLibc* will work elsewhere,
but not other way around.

Another deviance (at least for current version) is that input functions do not distinguish
between EOF and error conditions. But in freestanding environment there is no concept of file,
consequently end-of-file condition makes no much sense anyway. So, if input fails, it must be
error of some sort.

Library extensions
------------------

While main purpose of *FsLibc* is to provide *compatible* functions, there are some which, while
not compatible, are just too useful to be left out. Especially if they come as a byproduct of
implementing the compatible ones.

* `memset_l()` - fill the memory using byte pattern from *long* argument. Very useful for filling
   memory with *0xDEADBEEF*-style patterns. Internally used by `memset()`.
* `strcpy_e()` - copy string, just as `strcpy()`, but return a pointer to the *end of dest* -
   pointing to terminating *\0* character. This way it is way more useful for string concatenation.
   More so - it's the natural value for *dest* after copying and additional steps are required to
   preserve original one.
* `strncpy_e()` - behaves just like `strncpy()`, but also returns pointer to the end of the string.
   Returned value points to address just after the last non-\0 character copied.

It is recommended to use standards compliant versions where possible, turning to extension ones only
when it is absolutely necessary (like - when you are about to implement it yourself anyway). Extension
functions are available from include file *fslc/stringx.h*.

Build and install
=================

*FsLibc* uses [CMake][cmake] build system to compile its sources. There are 3 build profiles defined:

* **Debug** - use while developing. Enables debugging information, code coverage information;
* **Release** - compiles without debug information, full code optimizations. Function names in
  compiled library are what is expected in *C Standard Library*. Use this mode to prepare library
  for linking into kernel;
* **RelCheck** - compiles with *almost release* settings. No debug info, full code optimization. The
  only difference from *Release* is that function names are still prefixed with `fslc_`. The purpose
  of this mode is to run unit tests on release code. Obviously, you still can not be absolutely sure if
  it will behave on different platform. But you may try to test on target platform running Linux.

For *Debug* and *RelCheck* the compile commands are almost identical:

    cmake -DCMAKE_BUILD_TYPE=Debug .
    make
    make test

**Warning**: do not attempt to run *make install* here, especially with elevated privileges. You risk
to overwrite your host system's header files.

For *Release* configuration, most likely, you will want to cross-compile the library for your
target platform. Edit file *cross-toolchain.cmake*, specify the compiler toolchain:

    # specify the cross compiler
    CMAKE_FORCE_C_COMPILER(/usr/local/cross/bin/arm-elf-eabi-gcc GNU)
    CMAKE_FORCE_CXX_COMPILER(/usr/local/cross/bin/arm-elf-eabi-g++ GNU)

This will switch compilers to *arm-elf-eabi* platform, installed at */usr/local/cross*. Now
configure the system:

    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=cross-toolchain.cmake \
          -DCMAKE_INSTALL_PREFIX=/home/devel/fslibc .
    make -C libc
    make -C libc install

This will compile the library and then install it at location */home/devel/fslibc* (you may want
to adjust it for your needs). Note that we are not even trying to build tests here. Most likely they
will not compile, and even if they did they would not run, as host and target platforms differ.

[cmake]: https://cmake.org/ "CMake"

Development and tests
=====================

As C library is one of most fundamental piece of software, it's a very good idea to make it as bug-free
as possible. *FsLibc* uses white-box unit tests with help of [UnitTest++][unittestpp] framework to ensure
correct behavior. The policy is to get 100% line and branch coverage at all times. If a bug is discovered,
it must be first reproduced with appropriate unit test and only then fixed.

[CodeLite][codelite] is used for development. Its *workspace* and *project* files are also included in
source files and coexist with [CMake][cmake] easily.

[unittestpp]: https://unittest-cpp.github.io/ "UnitTest++ framework"
[codelite]: http://codelite.org/ "CodeLite IDE"
