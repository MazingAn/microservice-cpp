cmake_minimum_required(VERSION 3.15)

project(queue)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/../include)
include_directories(${PROJECT_SOURCE_DIR}/../models)

aux_source_directory(. SRC)

link_libraries(models)

add_library(queue ${SRC})

target_link_libraries(queue rabbitmq)
