# find gtest
set(GTEST_FOUND FALSE)
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/googletest)
    add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
        "googletest"
    )
    set(GTEST_FOUND TRUE)
endif()

