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

# ================ Project ========================
# Project name and a few useful settings
project(print_ip
	VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}
	DESCRIPTION "OTUS c++ homeworks: ip_filter"
	LANGUAGES CXX
)

# boost for unit tests
include(find-boost)
if(NOT Boost_FOUND)
	message(FATAL_ERROR "Sorry, cannot work without Boost")
	exit()
endif()
include(project_target)
include(helpers)
include(c++-config)

if (ENABLE_TESTING)
	enable_testing()
endif()

# The library code is here
add_subdirectory(library)

# main apps are here
add_subdirectory(apps)