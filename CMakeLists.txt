cmake_minimum_required(VERSION 3.22)
project(banking_oop)

set(CMAKE_CXX_STANDARD 14)

add_executable(banking_oop main.cpp)
add_executable(banking account.cpp)
