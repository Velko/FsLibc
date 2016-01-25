cmake_minimum_required (VERSION 2.6)
project (FsLibc)

enable_testing()

set (FsLibc_VERSION_MAJOR 0)
set (FsLibc_VERSION_MINOR 8)

add_subdirectory(libc)
add_subdirectory(tests)
