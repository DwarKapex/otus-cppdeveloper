cmake .
# build lib
cmake --build . --target lib_Matrix
# build test for lib
cmake --build . --target test_Matrix
# run test
ctest test_Matrix
# build and install app
cmake --build . --target matrix
# generate deb package 
cpack
