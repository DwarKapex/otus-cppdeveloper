cmake .
# build lib
cmake --build . --target lib_struct
# build test for lib
cmake --build . --target test_struct
# run test
ctest test_struct
# build and install app
cmake --build . --target struct
# generate deb package 
cpack
