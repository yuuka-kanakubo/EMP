# Source files for library
add_library(EMP_LIB STATIC
	          ReadIn.cpp Write.cpp EMconv.cpp EMP.cpp EigenSolve.cpp
		  energymomentumtensor.cpp fourvector.cpp threevector.cpp
	   )
target_include_directories(EMP_LIB PUBLIC ${PROJECT_SOURCE_DIR}/include)
