cmake_minimum_required(VERSION 2.8)

project(Siemens CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(main src/main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})
