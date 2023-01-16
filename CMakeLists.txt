
# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

#enforce C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the project name
project (matrix_ops)

enable_testing()

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    tests/test_matrix.cpp
    src/matrix.cpp
    include/matrix.h
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(matrix src/matrix.cpp include/matrix.h)
target_link_libraries(matrix PRIVATE Threads::Threads)


# Add an executable with the above sources
add_executable(test_constructor tests/test_constructor.cpp include/matrix.h)
add_executable(test_mult tests/test_mult.cpp include/matrix.h)
add_executable(test_transpose tests/test_transpose.cpp include/matrix.h)

add_test(NAME test_constructor
        COMMAND test_constructor)

add_test(NAME test_mult
        COMMAND test_mult)

add_test(NAME test_transpose
        COMMAND test_transpose)

#hide test executables
set_target_properties(
    test_constructor test_mult test_transpose
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY bin/test
)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
#target_include_directories(test_matrix
#    PRIVATE 
#        ${PROJECT_SOURCE_DIR}/include
#)