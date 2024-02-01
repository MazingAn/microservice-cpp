cmake_minimum_required(VERSION 3.15)

project(model)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../rpc)

aux_source_directory(. SRC)

link_libraries(rpc)

add_library(models ${SRC})
