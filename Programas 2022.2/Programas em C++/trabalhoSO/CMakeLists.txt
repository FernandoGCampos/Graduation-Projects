cmake_minimum_required(VERSION 3.16)
project(trabalhoSO)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)
find_package(Threads)

add_executable(trabalhoSO main.cpp)
