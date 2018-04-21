cmake_minimum_required(VERSION 3.0)


set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -std=c++14 -O3 -DNDEBUG")

include_directories(../../ext/cnpy/)
include_directories(../../include/)

set(SRC
  main.cc
)

#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(npz2tbin ${SRC})
target_link_libraries(npz2tbin cnpy)


set_target_properties(npz2tbin
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)

