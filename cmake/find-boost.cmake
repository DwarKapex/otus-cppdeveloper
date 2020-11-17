# find boost
find_package(Boost 
	REQUIRED COMPONENTS unit_test_framework
)

message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libs: ${Boost_LIBRARIES}")
