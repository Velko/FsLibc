file(GLOB fslc_SRC src/*.c)
file(GLOB fslc_INC include/fslc/*.h)
file(GLOB fslc_SINC include/*.h)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -fprofile-arcs -ftest-coverage -DALT_FSLC_NAMES")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Wextra")
set(CMAKE_C_FLAGS_RELCHECK "${CMAKE_C_FLAGS_RELEASE} -DALT_FSLC_NAMES")

include_directories(include/fslc)
add_library(fslc ${fslc_SRC})

install(TARGETS fslc DESTINATION lib)
install(FILES ${fslc_SINC} DESTINATION include)
install(FILES ${fslc_INC} DESTINATION include/fslc)
