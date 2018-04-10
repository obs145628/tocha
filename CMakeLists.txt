cmake_minimum_required(VERSION 3.0)
project(Tocha)

add_subdirectory(./ext/cnpy/)

add_subdirectory(./src/npz2tbin/)
add_subdirectory(./src/tbin2npz/)
add_subdirectory(./src/tbin-dump/)
