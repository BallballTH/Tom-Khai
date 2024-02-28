#include <windows.h>
#include <mmsystem.h>
#include <iostream>

// #include "../dialogueMaker/dialogueMaker.h"
#pragma comment(lib, "winmm.lib")

class Playsound {
public:
    void static playsoundbg(const std::string& sceneId);
    void static playefsound(const std::string& sceneId); // add efsound ระหว่างเล่น bg ไม่ได้ทีTT 
    void static StopPlay();
};

void Playsound::playsoundbg(const std::string& sceneId) {
    if (sceneId == "begin") {
        PlaySound(TEXT("keyboard"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
}

void Playsound::playefsound(const std::string& sceneId) {
    if (sceneId == "1-1") {
        PlaySound(TEXT("magic"), NULL, SND_FILENAME | SND_ASYNC ); // add efsound ระหว่างเล่น bg ไม่ได้ทีTT
    }else if(sceneId == "1-2"){
        PlaySound(TEXT("magic"), NULL, SND_FILENAME | SND_ASYNC );
    }else if(sceneId == "2-1"){
        PlaySound(TEXT("magic"), NULL, SND_FILENAME | SND_ASYNC );
    }
    else if(sceneId == "2-2"){
        PlaySound(TEXT("magic"), NULL, SND_FILENAME | SND_ASYNC );
    }
}


void Playsound::StopPlay() {
    PlaySound(NULL, NULL, 0);
}


// int main() {
//     Playsound::playsoundbg("begin");
    
//     std::cout << "123456789\n"; //dialogue & options
//     int x;
//     std::cin >> x;

//     Playsound::StopPlay();

    

//     return 0;
// }

// Playsound::playefsound("1-2");
// Sleep(5000);

// cd "d:\cpp\project\Tom-Khai\Sound\"
// g++ sound.cpp -o sound -lwinmm
//./sound