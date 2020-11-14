cmake .
# build lib
cmake --build . --target libHelloWorld
# build test for lib
cmake --build . --target test_HelloWorld
# run test
ctest test_HelloWorld
# build and install app
cmake --build . --target helloworld
# generate deb package 
cpack
