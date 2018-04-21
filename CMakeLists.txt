cmake_minimum_required(VERSION 3.0)
project(Tocha)

set(CMAKE_CXX_FLAGS "-O3 -std=c++17")

add_subdirectory(./ext/cnpy/)

add_subdirectory(./src/npz2tbin/)
add_subdirectory(./src/tbin2npz/)
add_subdirectory(./src/tbin-diff/)
add_subdirectory(./src/tbin-dump/)
