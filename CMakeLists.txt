cmake_minimum_required (VERSION 2.6)
project (FsLibc)

option(ENABLE_TESTS "Enable Testings" OFF)
option(ENABLE_STANDARD_SYMNAMES "Enable Standard Symbol Names" OFF)

set (FsLibc_VERSION_MAJOR 0)
set (FsLibc_VERSION_MINOR 8)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Wextra")

add_subdirectory(libc)

if(ENABLE_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()
