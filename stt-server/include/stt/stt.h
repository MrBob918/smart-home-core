#ifndef STT_H
#define STT_H
#include "vosk_api.h"
#include <string>

class stt{
    public:
    stt(const char *modelPath, float simpleRate = 16000);
    
    ~stt();
    
    stt(const stt&) = delete;
    stt& operator=(const stt&) = delete;

    void transcribeAudio(const char *wavFilePath);
    
    std::string getFinalResult();

    void reset();
    
    private:
    VoskModel *p_vskModel;
    
    VoskRecognizer *p_vskRec;

    std::string m_rawText;
    
    enum m_errorType{
        modelLoadFailed,
        recognizerLoadFailed,
        fileOpenFailed,
        recongitionProcessFaild
    };
    
    void voskInit(const char *modelPath, float simpleRate);
    void voskKill();
    
    std::string extractTextFormJson(std::string);
    
    int errorCheck(m_errorType);
};


#endif // STT_H