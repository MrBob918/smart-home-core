cmake_minimum_required(VERSION 3.5)
project(STTServer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Добавляем путь к cmake модулям
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(DownloadVosk)
include(DownloadVoskModel)
include(CompileProto)

# Vosk library path
set(VOSK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/vosk-include)

# STT library path
set(STT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/stt)

set(STT_PROTO_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../proto/stt.proto) # stt.proto file

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${VOSK_DIR})
include_directories(${STT_DIR})

# Source files
file(GLOB_RECURSE STT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/stt/*.cpp)
set(MAIN_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/stt-main.cpp)

# Executable
add_executable(stt-server ${STT_SOURCES} ${MAIN_SOURCE})

target_add_protobuf(stt-server ${STT_PROTO_FILE}) # connect gRPC and protonbuf

# Link vosk library
target_link_libraries(stt-server ${VOSK_DIR}/libvosk.so grpc++ grpc protobuf::libprotobuf)

# Output directory
set_target_properties(stt-server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
