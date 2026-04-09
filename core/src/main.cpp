#include "vosk_api.h"
#include <fstream>
#include <iostream>

int main() {
    
    VoskModel *vskModel = vosk_model_new("models/vosk-model-small-ru-0.22");
    if (vskModel == NULL) {
        std::cerr << "Failed to create model\n";
        return -1;
    }

    VoskRecognizer *vskRec = vosk_recognizer_new(vskModel, 16000);
    if (vskRec == NULL) {
        std::cerr << "Failed to create recognizer\n";
        vosk_model_free(vskModel);
        return -1;
    }
    
    vosk_recognizer_set_words(vskRec, 1);

    std::ifstream wavFile("./Voice_test.wav", std::ios::binary);
    
    if (!wavFile.is_open()) {
        std::cerr << "Failed to open file\n";
        vosk_recognizer_free(vskRec);
        vosk_model_free(vskModel);
        return -1;
    }

    wavFile.seekg(44, std::ios::beg);

    const size_t BUFFER_SIZE = 1024;
    char BUFFER[BUFFER_SIZE];

    while (wavFile.read(BUFFER, BUFFER_SIZE) || wavFile.gcount() > 0) {
        std::streamsize bytesRead = wavFile.gcount();
        
        if (vosk_recognizer_accept_waveform(vskRec, BUFFER, bytesRead) == 1) {
            std::cout << vosk_recognizer_result(vskRec) << std::endl;
        }

    }
    
    wavFile.close();
    
    const char *result = vosk_recognizer_final_result(vskRec);
    std::cout << result << std::endl;

    vosk_recognizer_free(vskRec);
    
    vosk_model_free(vskModel);

} 