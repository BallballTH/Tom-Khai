#include "sound.h"
#include <iostream>

void Playsound::playsoundbg(const std::string& sceneId) {
    if (sceneId == "begin") {
        mciSendString("play Sound/sounds/musicbg.wav", NULL, 0, NULL); // PlaySound(TEXT("Sound/sounds/bgmusic"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }else if(sceneId == "ending_you_die"){
        mciSendString("play Sound/sounds/die.wav", NULL, 0, NULL);
    }else if(sceneId == "ending_execution"){
        mciSendString("play Sound/sounds/execution.wav", NULL, 0, NULL);
    }else if(sceneId == "ending1"){
        mciSendString("play Sound/sounds/ending1.wav", NULL, 0, NULL);
    }else if(sceneId == "ending2"){
        mciSendString("play Sound/sounds/ending2.wav", NULL, 0, NULL);
    }else if(sceneId == "ending3"){
        mciSendString("play Sound/sounds/ending3.wav", NULL, 0, NULL);
    }else return;
}

void Playsound::playsoundef(const std::string& statchange){
    char text[50];
    double amount;
    char operation;
    sscanf(statchange.c_str(), "%[^-+] %c %lf", text, &operation, &amount);
    std::string stat = text;
    
    if (operation == '-') {               
        if (stat == "hp") {
            mciSendString("play Sound/soundf/hurt.wav", NULL, 0, NULL);
            
        } else if (stat == "sa") {
            mciSendString("play Sound/soundf/sanityd.wav", NULL, 0, NULL);
        }

        
    } else if (operation == '+') {       
        if (stat == "hp") {
            mciSendString("play Sound/soundf/pop.wav", NULL, 0, NULL);

        } else if (stat == "sa") {
            mciSendString("play Sound/soundf/pop.wav", NULL, 0, NULL);
        }
    }else return;
}

void Playsound::StopPlay(const std::string& filename) {
    mciSendString("stop all", NULL, 0, 0);
}

