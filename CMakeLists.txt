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

find_package(Poco REQUIRED COMPONENTS Foundation Net XML Util Zip)

if (${Poco_FOUND})
    message(STATUS "Poco version: ${Poco_VERSION}")
    message(STATUS "Poco libs: ${Poco_LIBRARIES}")
else()
    message(FATAL_ERROR "Poco was not found")
endif()

add_executable(${PROJECT_NAME}
        handlers/RequestFactory.cpp
        handlers/get/GetFileHandler.cpp
        handlers/post/UploadFileHandler.cpp
        handlers/errors/ErrorHandler.cpp
        FileServerSubsystem.cpp
        FileServerApplication.cpp
        utils/utils.cpp
        main.cpp)

target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            yaml-cpp
            ${Poco_LIBRARIES})

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
