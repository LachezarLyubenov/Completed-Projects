cmake_minimum_required(VERSION 3.8)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bst.h
        data1.txt
        data2.txt
        test.cpp)

add_executable(src ${SOURCE_FILES})