cmake_minimum_required(VERSION 3.15)

project(rpc)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/../include)

aux_source_directory(. SRC)

add_library(rpc ${SRC})

target_link_libraries(rpc curl restclient-cpp)
