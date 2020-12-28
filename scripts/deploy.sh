cmake .
# build lib
cmake --build . --target lib_PrintIp
# build test for lib
cmake --build . --target test_PrintIp
# run test
ctest test_PrintIp
# build and install app
cmake --build . --target print_ip
# generate deb package 
cpack
