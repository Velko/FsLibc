file(GLOB fslc_SRC src/*.c)
file(GLOB fslc_INC include/fslc/*.h)
file(GLOB fslc_SINC include/*.h)

include_directories(include/fslc)
add_library(fslc ${fslc_SRC})

install(TARGETS fslc DESTINATION lib)
install(FILES ${fslc_SINC} DESTINATION include)
install(FILES ${fslc_INC} DESTINATION include/fslc)
