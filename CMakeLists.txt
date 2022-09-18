cmake_minimum_required(VERSION 3.22)
project(FileServer)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 17)

if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
    set(ADDITIONAL_LIB rt)
endif()


# Yaml config parser
add_subdirectory(third-party/yaml-cpp)


add_executable(FileServer
        main.cpp)


