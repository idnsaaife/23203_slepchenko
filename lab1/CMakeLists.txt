cmake_minimum_required(VERSION 3.10)

project(Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fprofile-arcs -ftest-coverage -g -fsanitize=address")

include_directories("${CMAKE_SOURCE_DIR}/../googletest/googletest/include")
link_directories("${CMAKE_SOURCE_DIR}/../googletest/build/lib")

add_executable(runTests HTtest.cpp HashTable.cpp List.cpp)
target_compile_options(runTests PRIVATE -coverage)
target_link_options(runTests PRIVATE -coverage)
target_link_libraries(runTests gtest gtest_main) 
