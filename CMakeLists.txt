cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

project(MultSource_Download_LT)

aux_source_directory(. DIR_SRC)

include_directories(./ ./LT)

add_subdirectory(./LT)

add_executable(main ${DIR_SRC})

target_link_libraries(main LT)

