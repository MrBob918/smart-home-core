#ifndef STT_H
#define STT_H
#include <optional>
#include <string>
#include "vosk_api.h"

class stt{
    public:
    stt(const char *modelPath, float simpleRate);
    
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

    std::string errorText;
    
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