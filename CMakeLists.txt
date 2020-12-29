# Work with CMake version minimum 3.12
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# set default travis-ci.org build if not defined one.
# Use for local build only
if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
	set(ENV{TRAVIS_BUILD_NUMBER} 42)
endif()

# Set repo cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# build options
option(ENABLE_TESTING "Build small (unit) tests" ON)
option(ENABLE_GTEST "Use Google Test Framework for testing" ON)
option(ENABLE_BOOST_TEST "Use Boost Unit Test Framework for testing" OFF)

# ================ Project ========================
# Project name and a few useful settings
project(struct
	VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}
	DESCRIPTION "OTUS c++ homeworks: ip_filter"
	LANGUAGES CXX
)

include(project_target)
include(helpers)
include(c++-config)

if (ENABLE_TESTING)
	if (ENABLE_GTEST AND ENABLE_BOOST_TEST)
		message(WARNING "Note: you try to use both Google and Boost Unit Test Frameworks")
	endif()

	# boost for unit tests
	if (ENABLE_BOOST_TEST)
		include(find-boost)
		if(NOT Boost_FOUND)
			message(FATAL_ERROR "Boost Unittest Framework was requested, but not found")
			exit()
		endif()
	endif()
	# gtest for unit tests
	if (ENABLE_GTEST)
		include(find-gtest)
		if(NOT GTEST_FOUND)
			message(FATAL_ERROR "Google Unittest Framework was requested, but not found")
			exit()
		endif()
	endif()

	enable_testing()
endif()

# The library code is here
add_subdirectory(library)

# main apps are here
add_subdirectory(apps)