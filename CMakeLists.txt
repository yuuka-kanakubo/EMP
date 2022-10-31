cmake_minimum_required(VERSION 2.8)


project(EMP, CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Ofast -Wall")

# GSL >=2.0 required
set(GSLCFLAGS "${GSLCFLAGS} gsl-config --cflags")
set(GSLLIBS "${GSLLIBS} gsl-config --libs")


add_subdirectory(src)
add_subdirectory(main)
