cmake_minimum_required(VERSION 3.24)
project(TinyRenderer)

set(CMAKE_CXX_STANDARD 11)

# Write targets to bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(src)