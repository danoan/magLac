cmake_minimum_required(VERSION 3.2)
project(magLac-test-coverage)

add_subdirectory(core/base/fundamental-combinator)
add_subdirectory(core/base/range)
add_subdirectory(core/multiple/resolver)
add_subdirectory(core/multiple/combinator)
add_subdirectory(core/single/combinator)
add_subdirectory(core/multithread)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    if (${COVERAGE})
        add_subdirectory(coverage)
    endif ()
endif ()