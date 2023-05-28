cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project("TypeList")

add_subdirectory("googletest")

enable_testing()

add_library(TypeList INTERFACE)
target_include_directories(TypeList INTERFACE "include")

add_subdirectory(test)
