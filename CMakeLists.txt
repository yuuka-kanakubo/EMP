cmake_minimum_required(VERSION 2.8)


project(EMP, CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Ofast -Wall")

# GSL >=2.0 required
find_package(GSL REQUIRED)

#set(CMAKE_VERBOSE_MAKEFILE on)

add_subdirectory(src)
add_subdirectory(main)
