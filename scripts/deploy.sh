project=Struct
binary_name=struct
cmake . -DENABLE_GTEST=ON -DENABLE_DOXYGEN=ON
# build lib
cmake --build . --target lib_$project
# build test for lib
cmake --build . --target test_$project
# run test
ctest test_$project
# build and install app
cmake --build . --target $binary_name
# build docs
cmake --build . --target docs
# generate deb package 
cpack
