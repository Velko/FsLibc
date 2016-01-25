file(GLOB tests_SRC *.cpp)

add_definitions(-std=c++11)

find_package(PkgConfig)
pkg_check_modules(PC_UTPP QUIET unittest++)

include_directories(${PROJECT_SOURCE_DIR}/libc/include)
include_directories(${PC_UTPP_INCLUDE_DIRS})
add_executable(tests ${tests_SRC})

target_link_libraries(tests fslc)
target_link_libraries(tests ${PC_UTPP_LIBRARIES})

add_test(libTests tests)

