cmake_minimum_required(VERSION 3.0)
project(ClownLib)

add_library(ClownLib include/ClownLib/ClownLib.h src/ClownLib.cpp)
target_include_directories(ClownLib PUBLIC include/)