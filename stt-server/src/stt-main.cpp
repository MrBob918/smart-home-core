#include "stt.h"
#include "gens/proto/stt.pb.h"
#include "gens/proto/stt.grpc.pb.h"
#include <iostream>
int main() {
    stt sttClass("./models/vosk-model-small-ru-0.22", 44100);
    sttClass.transcribeAudio("./Voice_test.wav");
    std::cout << sttClass.getFinalResult() << std::endl;
}