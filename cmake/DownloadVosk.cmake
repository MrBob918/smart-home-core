if(NOT EXISTS ${CMAKE_SOURCE_DIR}/core/include/vosk-include/libvosk.so OR NOT EXISTS ${CMAKE_SOURCE_DIR}/core/include/vosk-include/vosk_api.h)
file(DOWNLOAD https://github.com/alphacep/vosk-api/releases/download/v0.3.45/vosk-linux-aarch64-0.3.45.zip ${CMAKE_SOURCE_DIR}/core/include/vosk-linux-aarch64-0.3.45.zip STATUS DownloadVoskStatus SHOW_PROGRESS)

list(GET DownloadVoskStatus 0 DownloadVoskStatus_code)
list(GET DownloadVoskStatus 1 DownloadVoskStatus_message)

if(DownloadVoskStatus_code EQUAL 0)
    message(STATUS "Download successful!")
else()
    message(FATAL_ERROR "Download failed: ${DownloadVoskStatus_message}")
endif()

file(ARCHIVE_EXTRACT INPUT ${CMAKE_SOURCE_DIR}/core/include/vosk-linux-aarch64-0.3.45.zip DESTINATION ${CMAKE_SOURCE_DIR}/core/include/)

file(COPY ${CMAKE_SOURCE_DIR}/core/include/vosk-linux-aarch64-0.3.45/ DESTINATION ${CMAKE_SOURCE_DIR}/core/include/vosk-include/)
file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/core/include/vosk-linux-aarch64-0.3.45)

file(REMOVE ${CMAKE_SOURCE_DIR}/core/include/vosk-linux-aarch64-0.3.45.zip)

endif()