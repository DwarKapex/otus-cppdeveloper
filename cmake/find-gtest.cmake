#find gtest
set(GOOGLETEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/googletest CACHE STRING "Google Test source root")

if (EXISTS ${GOOGLETEST_ROOT})
    set(GTEST_FOUND TRUE)
    add_subdirectory(
        "${GOOGLETEST_ROOT}"
        "googletest"
    )
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
else()
    set(GTEST_FOUND FALSE)
endif()

