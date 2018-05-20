cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -std=c++17 -O3 -DNDEBUG")

include_directories(../../include/)

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

set(SRC
  main.cc
)

add_executable(npz2tbin ${SRC})
target_link_libraries(npz2tbin ${ZLIB_LIBRARIES})

set_target_properties(npz2tbin
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)
