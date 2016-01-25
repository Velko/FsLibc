file(GLOB fslc_SRC src/*.c)

add_definitions(-DALT_FSLC_NAMES)
include_directories(include)
add_library(fslc ${fslc_SRC})
