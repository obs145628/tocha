cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -std=c++14 -O3 -DNDEBUG")

include_directories(../../include/)

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

set(SRC
  main.cc
)

add_executable(tbin-dump ${SRC})
target_link_libraries(tbin-dump ${ZLIB_LIBRARIES})

set_target_properties(tbin-dump
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)
