INCLUDE(CMakeForceCompiler)

# this one is important
SET(CMAKE_SYSTEM_NAME Generic)

# specify the cross compiler
CMAKE_FORCE_C_COMPILER(/usr/local/cross/bin/arm-elf-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(/usr/local/cross/bin/arm-elf-eabi-g++ GNU)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
