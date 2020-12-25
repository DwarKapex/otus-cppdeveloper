cmake .
# build lib
cmake --build . --target lib_IpFilter
# build test for lib
cmake --build . --target test_IpFilter
# run test
ctest test_IpFilter
# build and install app
cmake --build . --target ip_filter
# generate deb package 
cpack
