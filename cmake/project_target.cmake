function(add_project_library)
	get_filename_component(lib_name "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
	set(lib_name lib_${lib_name})
	glob_target_files(${lib_name} 
					  TARGET_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

	# Verify content
    if ((NOT ${lib_name}_SOURCE) AND (NOT ${lib_name}_HEADER))
        message(FATAL_ERROR "Target ${lib_name} added in ${CMAKE_CURRENT_SOURCE_DIR} does not have any source files (must be in 'src' or 'include' subdirectories).")
	endif()
	
	add_library(${lib_name}
		STATIC
		${${lib_name}_SOURCE}
	)
	# set target properties
	set_target_properties(${lib_name} PROPERTIES
    	CXX_STANDARD 17
    	CXX_STANDARD_REQUIRED ON
	)

	# Set the includes property. This should automatically populate the include directories of any
	# targets who link to ${lib_name} at build time.
	list (GET ${lib_name}_HEADER 0 target_INCLUDE_DIRS_FIRST)
	target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endfunction()

function(add_project_test)
	if (NOT ENABLE_TESTING)
		return()
	endif()
	# Generate default test
	get_filename_component(test_dir "${CMAKE_CURRENT_SOURCE_DIR}" PATH)
	get_filename_component(target_name "${test_dir}" NAME)
	set(test_name test_${target_name})

	glob_target_files(${test_name} 
					  TARGET_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
	# Verify content
    if ((NOT ${test_name}_SOURCE) AND (NOT ${test_name}_HEADER))
        message(FATAL_ERROR "Target ${lib_name} added in ${CMAKE_CURRENT_SOURCE_DIR} does not have any source files (must be in 'src' or 'include' subdirectories).")
	endif()
	
	add_executable(${test_name}
		${${test_name}_SOURCE}
	)
	
	if (ENABLE_BOOST_TEST)
		set_target_properties(${test_name} PROPERTIES
			COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
			INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
			CXX_STANDARD 17
			CXX_STANDARD_REQUIRED ON
		)
	
		target_link_libraries(${test_name} 
			lib_${target_name}
			${Boost_LIBRARIES}
		)
	elseif(ENABLE_GTEST)
		set_target_properties(${test_name} PROPERTIES
			CXX_STANDARD 17
			CXX_STANDARD_REQUIRED ON
		)

		target_link_libraries(${test_name}
			lib_${target_name}
    		gtest gtest_main
		)
	endif()

	add_test(${test_name} ${test_name})
endfunction()

function(add_and_install_project_app app_name)
	set(options "")
    set(oneValueArgs "")
    set(multiValueArgs DEPEND)

    cmake_parse_arguments(add_project_app "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	glob_target_files(${app_name} 
					TARGET_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

	# Verify content
	if ((NOT ${app_name}_SOURCE) AND (NOT ${app_name}_HEADER))
		message(FATAL_ERROR "Target ${app_name} added in ${CMAKE_CURRENT_SOURCE_DIR} does not have any source files (must be in 'src' or 'include' subdirectories).")
	endif()

	add_executable(${app_name}
		${${app_name}_SOURCE}
	)

	set(app_lib_dependency "")
	foreach(link_lib ${add_project_app_DEPEND})
		LIST(APPEND app_lib_dependency ${link_lib})
	endforeach()
	
	target_link_libraries(${app_name}
		${app_lib_dependency}	
	)	
	# set target properties
	set_target_properties(${app_name} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
	)

	# Set the includes property. This should automatically populate the include directories of any
	# targets who link to ${app_name} at build time.
	list (GET ${app_name}_HEADER 0 target_INCLUDE_DIRS_FIRST)
	target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

	# install
	install(TARGETS ${app_name} RUNTIME DESTINATION bin)

	# create deb package
	set(CPACK_GENERATOR DEB)
	set(CPACK_DEBIAN_PACKAGE_MAINTAINER KK)
	set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
	set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
	set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
	set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
	include(CPack)

endfunction()