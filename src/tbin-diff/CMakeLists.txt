cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -std=c++14 -O3 -DNDEBUG")

include_directories(../../ext/cnpy/)
include_directories(../../include/)

set(SRC
  main.cc
)

add_executable(tbin-diff ${SRC})
target_link_libraries(tbin-diff cnpy)

set_target_properties(tbin-diff
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)
