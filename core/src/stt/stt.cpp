#include "stt.h"
#include <fstream>
#include <iostream>
stt::stt(const char *modelPath, float simpleRate) {
    voskInit(modelPath, simpleRate);
}

void stt::voskInit(const char *modelPath, float simpleRate){
    p_vskModel = vosk_model_new(modelPath);
    if(p_vskModel == nullptr) {
        errorCheck(m_errorType::modelLoadFailed);
    }
    p_vskRec = vosk_recognizer_new(p_vskModel, simpleRate);
    if(p_vskRec == nullptr) {
        errorCheck(m_errorType::recognizerLoadFailed);
    }
}
void stt::voskKill(){
    vosk_recognizer_free(p_vskRec);
    vosk_model_free(p_vskModel);
}

stt::~stt(){
    stt::voskKill();
}

void stt::transcribeAudio(const char* wavFilePath) {
    std::ifstream fileStream(wavFilePath, std::ios::binary);
    if(!fileStream.is_open()){
        errorCheck(m_errorType::fileOpenFailed);
    }
    fileStream.seekg(44, std::ios::beg);

    const size_t BUFFER_SIZE = 4000;
    char buffer[BUFFER_SIZE];

    while(fileStream.read(buffer, BUFFER_SIZE) || fileStream.gcount() > 0) {
        size_t bytesLeft = fileStream.gcount();
        short incomplitResult = vosk_recognizer_accept_waveform(p_vskRec, buffer, bytesLeft);
        if(incomplitResult == -1){
            errorCheck(m_errorType::recongitionProcessFaild);
            fileStream.close();
        }
    }
    stt::m_rawText = vosk_recognizer_final_result(p_vskRec);
    fileStream.close();
}

std::string stt::getFinalResult() {
    std::cout << m_rawText;
    return m_rawText;
}

int stt::errorCheck(m_errorType error){
    switch (error)
    {
    case m_errorType::modelLoadFailed :
        std::cerr << "Can't load your model, check directory with model or path!" << std::endl;
        stt::voskKill();
        std::abort();
    case m_errorType::recognizerLoadFailed :
        std::cerr << "Can't create recognaizer" << std::endl;
        stt::voskKill();
        std::abort();
    case m_errorType::fileOpenFailed :
        std::cerr << "Cant open wav file!" << std::endl;
        stt::voskKill();
        std::abort();
    case m_errorType::recongitionProcessFaild :
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
    vosk_recognizer_reset(p_vskRec);
    stt::m_rawText.clear();
}

std::string stt::extractTextFormJson(std::string m_rawText) {
}