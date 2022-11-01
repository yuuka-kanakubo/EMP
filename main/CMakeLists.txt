set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}
   )
add_executable(EMP main.cpp)
target_link_libraries(EMP EMP_LIB)
target_link_libraries(EMP GSL::gsl GSL::gslcblas)
