# Source files for library
add_library(EMP_LIB STATIC
	          ReadIn.cpp Write.cpp EMconv.cpp EMtensFromPartons.cpp
	   )
target_include_directories(EMP_LIB PUBLIC ${PROJECT_SOURCE_DIR}/include)
