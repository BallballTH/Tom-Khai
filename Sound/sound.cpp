#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#pragma comment(lib, "winmm.lib")

int main() {
    PlaySound(TEXT("D:\\cpp\\project\\Tom-Khai\\Sound\\soundd\\magic.wav"), NULL, SND_FILENAME | SND_SYNC);
    return 0;
}