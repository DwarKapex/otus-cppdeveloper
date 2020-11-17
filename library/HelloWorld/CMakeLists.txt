add_project_library()

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/include/HelloWorld/version.h.in" 
                "${CMAKE_CURRENT_SOURCE_DIR}/include/HelloWorld/version.h")

add_subdirectory(test)