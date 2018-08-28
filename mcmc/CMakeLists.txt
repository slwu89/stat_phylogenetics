cmake_minimum_required(VERSION 3.12)
project(mcmc)

set(CMAKE_CXX_STANDARD 14)

add_executable(mcmc main.cpp RandomVariable.cpp RandomVariable.h)