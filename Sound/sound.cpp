#include <windows.h>
#include <mmsystem.h>
#include <iostream>

// #include "../dialogueMaker/dialogueMaker.h"
#pragma comment(lib, "winmm.lib")

class Playsound {
public:
    void static playsoundbg(const std::string& sceneId);
    // void static playefsound(const std::string& sceneId);
    void static StopPlay();
};

void Playsound::playsoundbg(const std::string& sceneId) {
    if (sceneId == "begin") {
        PlaySound(TEXT("keyboard"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
}

// void Playsound::playefsound(const std::string& sceneId) {
//     if (sceneId == "1-2") {
//         PlaySound(TEXT("magic"), NULL, SND_FILENAME | SND_ASYNC );
//     }
// }


void Playsound::StopPlay() {
    PlaySound(NULL, NULL, 0);
}


int main() {
    Playsound::playsoundbg("begin");

    std::cout << "123456789\n"; //test
    int x;
    std::cin >> x;

    Playsound::StopPlay();

    
    // Playsound::playefsound("1-2");
    // Sleep(5000);

    return 0;
}

// cd "d:\cpp\project\Tom-Khai\Sound\"
// g++ sound.cpp -o test -lwinmm
//.\test