cmake_minimum_required(VERSION 3.10)
project(fls C)

file(GLOB SOURCES "src/*.c")

add_library(fls STATIC ${SOURCES})

target_include_directories(fls PUBLIC include)

install(TARGETS fls ARCHIVE DESTINATION lib)

install(DIRECTORY include/ DESTINATION include)
