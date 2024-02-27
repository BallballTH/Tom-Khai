#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include "../dialogueMaker/dialogueMaker.h"
#pragma comment(lib, "winmm.lib")

class PlaySound{
    public:
        void playsoundss(string);
        void StopPlay();
};

void PlaySound::playsoundss(string sceneId){
    switch(sceneId){
        case "1-2":
            PlaySound(TEXT("keyboard"), NULL, SND_FILENAME | SND_ASYNC);

    }
}

void PlaySound::StopPlay(){
    PlaySound(NULL, NULL, 0);
}


int main() {
    
    {PlaySound(TEXT("keyboard"), NULL, SND_FILENAME | SND_ASYNC); Sleep(10000);} //play 5 sec

    // PlaySound(NULL, NULL, 0);
    // Sleep(5000);

    return 0;
}

// cd "d:\cpp\project\Tom-Khai\Sound\"
// g++ sound.cpp -o test -lwinmm
//.\test