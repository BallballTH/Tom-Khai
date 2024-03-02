#include "sound.h"

void Playsound::playsoundbg(const std::string& sceneId) {
    if (sceneId == "begin") {
        // PlaySound(TEXT("Sound/sounds/bgmusic"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        mciSendString("play Sound/sounds/musicbg.wav", NULL, 0, NULL);
    }
}

void Playsound::playsoundef(const std::string& statchange){
    char text[50];
    double amount;
    char operation;
    sscanf(statchange.c_str(), "%s %c %lf", text, &operation, &amount);

    if(operation == '-'){
        // PlaySound(TEXT("Sound/soundf/hurt"), NULL, SND_FILENAME | SND_ASYNC );
        mciSendString("play Sound/soundf/hurt.wav", NULL, 0, NULL);
    }else if(operation == '+'){
        mciSendString("play Sound/soundf/pop.wav", NULL, 0, NULL);
        // PlaySound(TEXT("Sound/soundf/pop"), NULL, SND_FILENAME | SND_ASYNC );
    }else return;
}

void Playsound::StopPlay() {
    PlaySound(NULL, NULL, 0);
}

