cmake_minimum_required(VERSION 3.15)

project(dc)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/../include/nacos)

aux_source_directory(. SRC)

add_library(dc ${SRC})
