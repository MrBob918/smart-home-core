#include "stt.h"
int main() {
    stt sttClass("./models/vosk-model-small-ru-0.22", 44100);
    sttClass.transcribeAudio("./Voice_test.wav");
    sttClass.getFinalResult();
}