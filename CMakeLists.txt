cmake_minimum_required(VERSION 3.13)

project(navi)

set(CMAKE_CXX_STANDARD 17)
set(WARNING_FLAGS "-Wall -Wextra -pedantic")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

message("Compile flags: ${CMAKE_CXX_FLAGS}")

add_subdirectory(app)
add_subdirectory(core)
add_subdirectory(externals)
