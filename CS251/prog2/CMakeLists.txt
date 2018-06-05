cmake_minimum_required(VERSION 3.8)
project(cs251prog2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        driver.cpp
        GridWorld.h
        GWInterface.h)

add_executable(cs251prog2 ${SOURCE_FILES})