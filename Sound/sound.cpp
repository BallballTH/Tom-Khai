#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include "../dialogueMaker/dialogueMaker.h"
#pragma comment(lib, "winmm.lib")

int main() {

    {PlaySound(TEXT("keyboard"), NULL, SND_FILENAME | SND_ASYNC); Sleep(5000);} //play 5 sec

    // PlaySound(NULL, NULL, 0);
    // Sleep(5000);

    return 0;
}

// cd "d:\cpp\project\Tom-Khai\Sound\"
// g++ sound.cpp -o test -lwinmm
//.\test