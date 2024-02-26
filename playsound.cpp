#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include "dialogueMaker/dialogueMaker.h"
#pragma comment( lib, "winmm.lib" )

int main()
{
    std::cout << "hello";
    PlaySound(TEXT("ALARMM"), NULL, SND_FILENAME);
    std::cout << "wow";
    return 0;
}