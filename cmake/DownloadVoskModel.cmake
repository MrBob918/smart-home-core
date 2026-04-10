if(NOT EXISTS ${CMAKE_BINARY_DIR}/models/vosk-model-small-ru-0.22/)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/models/)
file(DOWNLOAD https://alphacephei.com/vosk/models/vosk-model-small-ru-0.22.zip ${CMAKE_BINARY_DIR}/models/vosk-model-small-ru-0.22.zip STATUS DownloadVoskModelStatus SHOW_PROGRESS)

list(get DownloadVoskModelStatus 0 DownloadVoskModelStatus_code)
list(get DownloadVoskModelStatus 1 DownloadVoskModelStatus_message)

if(DownloadVoskModelStatus_code EQUAL 0)
    message("Download succesful")
else()
    message(FATAL_ERROR "Error: ${DownloadVoskModelStatus_message}")
endif()

file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/models/vosk-model-small-ru-0.22.zip DESTINATION ${CMAKE_BINARY_DIR}/models/vosk-model-small-ru-0.22)
file(REMOVE ${CMAKE_BINARY_DIR}/models/vosk-model-small-ru-0.22.zip)
endif()