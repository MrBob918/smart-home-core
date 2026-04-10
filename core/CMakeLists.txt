cmake_minimum_required(VERSION 3.15)
project(Core VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#create list cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(DownloadVosk) #call Download vosk module
include(DownloadVoskModel)

# Vosk library path
set(VOSK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/vosk-include)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${VOSK_DIR})

# Source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Executable
add_executable(core ${SOURCES})

# Link vosk library
target_link_libraries(core ${VOSK_DIR}/libvosk.so)

# Set output directory
set_target_properties(core PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
