cmake .
# build lib
cmake --build . --target lib_Allocator
# build test for lib
cmake --build . --target test_Allocator
# run test
ctest test_Allocator
# build and install app
cmake --build . --target allocator
# generate deb package 
cpack
