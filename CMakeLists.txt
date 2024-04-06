cmake_minimum_required(VERSION 3.10)
project(RedBlackTree)

set(CMAKE_CXX_COMPILER g++-13)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(rbt Main.cpp)
# target_include_directories(rbt PUBLIC "..")

