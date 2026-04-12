#include "stt.h"
#include <fstream>
#include <iostream>
#include <ranges>
#include <algorithm>
stt::stt(const char *f_modelPath, float f_simpleRate) {
    voskInit(f_modelPath, f_simpleRate);
}

void stt::voskInit(const char *f_modelPath, float f_simpleRate){
    p_vskModel = vosk_model_new(f_modelPath);
    if(p_vskModel == nullptr) {
        errorCheck(m_errorType::modelLoadFailed);
    }
    
    p_vskRec = vosk_recognizer_new(p_vskModel, f_simpleRate);
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

void stt::transcribeAudio(const char* f_wavFilePath) {
    std::ifstream _fileStream(f_wavFilePath, std::ios::binary);
    if(!_fileStream.is_open()){
        errorCheck(m_errorType::fileOpenFailed);
    }
    
    _fileStream.seekg(44, std::ios::beg);

    constexpr size_t _BUFFER_SIZE = 4000;
    char _buffer[_BUFFER_SIZE];

    while(_fileStream.read(_buffer, _BUFFER_SIZE) || _fileStream.gcount() > 0) {
        size_t _bytesLeft = _fileStream.gcount();
        
        short _uncomplitResult = vosk_recognizer_accept_waveform(p_vskRec, _buffer, _bytesLeft);
        if(_uncomplitResult == -1){
            errorCheck(m_errorType::recongitionProcessFaild);
            _fileStream.close();
        }
    }
    
    stt::m_rawText = vosk_recognizer_final_result(p_vskRec);
    _fileStream.close();
}

std::string stt::extractTextFormJson(std::string f_jsonTypeText) {
    auto _iterOfBufferTextStart = std::ranges::find(f_jsonTypeText, ':');
    
    size_t _bufferTextStart = std::ranges::distance(f_jsonTypeText.begin(), _iterOfBufferTextStart);
    size_t _bufferTextEnds = std::ranges::distance(_iterOfBufferTextStart, f_jsonTypeText.end());
    
    size_t _bufferTextLenght = _bufferTextEnds - _bufferTextStart;

    std::string _bufferText = f_jsonTypeText.substr(_bufferTextStart, _bufferTextLenght);

    auto _iterOfTextStart = std::ranges::find(f_jsonTypeText, '"');
    
    size_t _textStart = std::ranges::distance(_bufferText.begin(), _iterOfTextStart);
    size_t _textEnds = _bufferText.rfind('"');
    

    size_t _textLenght = _textEnds - _textStart;
    
    std::string _clearText = _bufferText.substr(_textStart, _textLenght);
    
    return _clearText;
}

std::string stt::getFinalResult() {    
    std::string _clearText = extractTextFormJson(m_rawText);
    return _clearText;
}

int stt::errorCheck(m_errorType f_error){
    switch (f_error)
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