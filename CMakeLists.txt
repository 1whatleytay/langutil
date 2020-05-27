cmake_minimum_required(VERSION 3.16)
project(langutil)

set(CMAKE_CXX_STANDARD 11)

add_library(langutil STATIC
    include/langutil/parser.h

    src/parser.cpp)

target_include_directories(langutil PUBLIC include)
