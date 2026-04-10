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
    VoskModel *vskModel;
    
    VoskRecognizer *vskRec;

    std::string rawText;
    
    enum errorType{
        modelLoadFailed,
        recognizerLoadFailed,
        fileOpenFailed,
        recongitionProcessFaild
    };
    
    void voskInit();
    void voskKill();
    
    std::string extractTextFormJson(std::string);
    
    int errorCheck(errorType);
};


#endif // STT_H