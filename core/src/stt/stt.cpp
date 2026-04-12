#include "stt.h"
#include <fstream>
#include <iostream>
stt::stt(const char *modelPath, float simpleRate) {
    voskInit(modelPath, simpleRate);
}

void stt::voskInit(const char *modelPath, float simpleRate){
    vskModel = vosk_model_new(modelPath);
    if(vskModel == nullptr) {
        errorCheck(errorType::modelLoadFailed);
    }
    vskRec = vosk_recognizer_new(vskModel, simpleRate);
    if(vskRec == nullptr) {
        errorCheck(errorType::recognizerLoadFailed);
    }
}
void stt::voskKill(){
    vosk_recognizer_free(vskRec);
    vosk_model_free(vskModel);
}

stt::~stt(){
    stt::voskKill();
}

void stt::transcribeAudio(const char* wavFilePath) {
    std::ifstream fileStream(wavFilePath, std::ios::binary);
    if(!fileStream.is_open()){
        errorCheck(errorType::fileOpenFailed);
    }
    fileStream.seekg(44, std::ios::beg);

    const size_t bufferSize = 4000;
    char buffer[bufferSize];

    while(fileStream.read(buffer, bufferSize) || fileStream.gcount() > 0) {
        size_t bytesLeft = fileStream.gcount();
        short incomplitResult = vosk_recognizer_accept_waveform(vskRec, buffer, bytesLeft);
        if(incomplitResult == -1){
            errorCheck(errorType::recongitionProcessFaild);
            fileStream.close();
        }
    }
    stt::rawText = vosk_recognizer_final_result(vskRec);
    fileStream.close();
}

std::string stt::getFinalResult() {
    std::cout << rawText;
    return rawText;
}

int stt::errorCheck(errorType error){
    switch (error)
    {
    case errorType::modelLoadFailed :
        std::cerr << "Can't load your model, check directory with model or path!" << std::endl;
        stt::voskKill();
        std::abort();
    case errorType::recognizerLoadFailed :
        std::cerr << "Can't create recognaizer" << std::endl;
        stt::voskKill();
        std::abort();
    case errorType::fileOpenFailed :
        std::cerr << "Cant open wav file!" << std::endl;
        stt::voskKill();
        std::abort();
    case errorType::recongitionProcessFaild :
        std::cerr << "At recognition your audio file was error!" << std::endl;
        stt::voskKill();
        std::abort();
    default:
        std::cerr << "No errors find!" << std::endl;
        return 0;
    }
    return 30;
}

void stt::reset(){
    vosk_recognizer_reset(vskRec);
    stt::rawText.clear();
}

std::string stt::extractTextFormJson(std::string text) {
    return text;
}