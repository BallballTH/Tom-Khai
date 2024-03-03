#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#pragma comment(lib, "winmm.lib")

class Playsound {
public:
    void static playsoundbg(const std::string& sceneId);
    void static playsoundef(const std::string& statchange);
    void static StopPlay(const std::string& filename);
};


