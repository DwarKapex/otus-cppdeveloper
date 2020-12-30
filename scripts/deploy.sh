project_name=Matrix
binary_name=matrix
cmake .
# build lib
cmake --build . --target lib_$project_name
# build test for lib
cmake --build . --target test_$project_name
# run test
ctest test_$project_name
# build and install app
cmake --build . --target $binary_name
# generate deb package 
cpack
