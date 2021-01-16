if (ENABLE_DOXYGEN)
  message(STATUS "doxygen enabled (ENABLE_DOXYGEN = ON)")
  
  # check if Doxygen is installed
  find_package(Doxygen
              REQUIRED dot
	            OPTIONAL_COMPONENTS mscgen dia
  )
  if (DOXYGEN_FOUND)
    # set input and output files
    set(doxyfile_in ${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    message(STATUS "doxygen documentation will be built in ${CMAKE_CURRENT_BINARY_DIR}/docs/html")
  else ()
    message(WARNING "doxygen and graphviz need to be installed to generate the doxygen documentation")
  endif ()
else()
    message(STATUS "doxygen disabled (ENABLE_DOXYGEN = OFF), no documentation will be built for project ${PROJECT_NAME}")
endif()

