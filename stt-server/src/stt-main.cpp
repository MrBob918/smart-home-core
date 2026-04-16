#include "stt.h"
#include "stt.pb.h"
#include "stt.grpc.pb.h"
#include <iostream>
int main() {
    stt sttClass("./models/vosk-model-small-ru-0.22", 44100);
    sttClass.transcribeAudio("./Voice_test.wav");
    std::cout << sttClass.getFinalResult() << std::endl;
}