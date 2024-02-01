cmake_minimum_required(VERSION 3.15)

project(fdpp)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(helpers)
add_subdirectory(rpc)
add_subdirectory(models)
add_subdirectory(queue)
add_subdirectory(db)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/helpers)
include_directories(${PROJECT_SOURCE_DIR}/rpc)
include_directories(${PROJECT_SOURCE_DIR}/models)
include_directories(${PROJECT_SOURCE_DIR}/queue)
include_directories(${PROJECT_SOURCE_DIR}/db)

link_directories(${PROJECT_SOURCE_DIR}/lib)

link_libraries(helpers)
link_libraries(rpc)
link_libraries(models)
link_libraries(queue)
link_libraries(db)

add_executable(fdpp main.cpp)
