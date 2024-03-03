#include "sound.h"
#include <iostream>

void Playsound::playsoundbg(const std::string& sceneId) {
    if (sceneId == "begin") {                                                                   // game start
        Playsound::StopPlay();
        mciSendString("play Sound/sounds/musicbg.wav", NULL, 0, NULL);  
    }
    else if(sceneId == "ending_you_die" || "ending_you_die_hp" || "ending_you_die_sa"){         // game end (you died)
        Playsound::StopPlay();
        mciSendString("play Sound/sounds/die.wav", NULL, 0, NULL);
    }
    else if(sceneId == "ending_execution"){                                                     // game end (ศาลประหารชีวิต)
        Playsound::StopPlay();
        mciSendString("play Sound/sounds/execution.wav", NULL, 0, NULL);
    }
    else if(sceneId == "ending1"){                                                              // game end (good end)
        Playsound::StopPlay();
        mciSendString("play Sound/sounds/ending1.wav", NULL, 0, NULL);
    }
    else if(sceneId == "ending2"){                                                              // game end (normal end)
        Playsound::StopPlay();  
        mciSendString("play Sound/sounds/ending2.wav", NULL, 0, NULL);
    }
    else if(sceneId == "ending3"){                                                              // game end (bad end)
        Playsound::StopPlay();
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

void Playsound::StopPlay() {
    mciSendString("close all", NULL, 0, 0);
}

