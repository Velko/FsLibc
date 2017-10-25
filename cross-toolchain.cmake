SET(CMAKE_SYSTEM_NAME Generic)

# specify the cross compiler
SET(CMAKE_C_COMPILER arm-elf-eabi-gcc)
SET(CMAKE_CXX_COMPILER arm-elf-eabi-g++)

# use this if CMAKE complains about '-rdynamic'
SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
