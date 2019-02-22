cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")

project(MultSource_Download_LT)

aux_source_directory(. DIR_SRC)

include_directories(./ ./LT)

add_subdirectory(./LT)

add_executable(main ${DIR_SRC})

target_link_libraries(main LT)

