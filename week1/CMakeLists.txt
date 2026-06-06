cmake_minimum_required(VERSION 3.25)
project(fastexponentiation)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 26)

add_executable(fastexponentiation fastexponentiation.cpp)
