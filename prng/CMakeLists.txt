cmake_minimum_required(VERSION 3.12)
project(prng)

set(CMAKE_CXX_STANDARD 14)

add_executable(prng main.cpp RandomVariable.cpp RandomVariable.h)