cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -std=c++14 -O3 -DNDEBUG")

include_directories(../../include/)

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

set(SRC
  main.cc
)

#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(tbin2npz ${SRC})
target_link_libraries(tbin2npz ${ZLIB_LIBRARIES})


set_target_properties(tbin2npz
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)

