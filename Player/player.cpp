#include "player.h"
#include <iostream>

void movecursor(int x_position=0,int y_postion=0){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);        // Get handle to console output
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(hConsole, &csbi);              // Get CurrentCursor
    COORD screen = csbi.dwCursorPosition;

    screen.X += x_position;
    screen.Y += y_postion;
    SetConsoleCursorPosition(hConsole, screen);               // move Cursor
}

int currentcursor(char position){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);        // Get handle to console output
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(hConsole, &csbi);              // Get CurrentCursor
    COORD screen = csbi.dwCursorPosition;

    if(position == 'x') return screen.X;
    else if(position == 'y') return screen.Y;
    else return 0;
}

void player::printstats(){
    double percent_hp = hp/hpmax;
    double percent_sa = sanity/sanity_max;

    _setmode(_fileno(stdout),_O_U16TEXT);       // Set console output to UTF-16

    //printHP
    movecursor(50);
    int tempX = currentcursor('x');             // Get Current position for pirnt Sanity bar

    std::wcout << L"HP: ";
    for(int i=0; i<20; i++){
        std::wcout << L"\u2591";                    // \u2591,\u2588 are unicodes used for print HP and SA bar
    }
    movecursor(-20);
    for(int i=0; i<percent_hp*20; i++){
        std::wcout << L"\u2588";
    }

    std::wcout<<"\r";                   // move cursor back to start
    //printSanity

    movecursor(tempX+30);
    std::wcout << L"SA: ";
    for(int i=0; i<20; i++){
        std::wcout << L"\u2591";
    }
    movecursor(-20);
    for(int i=0; i<percent_sa*20; i++){
        std::wcout << L"\u2588";
    }

    _setmode(_fileno(stdout), _O_TEXT);              // Set console output to default before its changed

}

void player::changestat(const std::string& change) {
    char text[50];
    double amount;
    char operation;

    sscanf(change.c_str(), "%[^-+] %c %lf", text, &operation, &amount);
    std::string stat = text;
    // Check the operation
    if (operation == '-') {               // Decrease the stat
        if (stat == "hp") {
            hp -= amount;
            if(hp<0) hp = 0;
            
        } else if (stat == "sa") {
            sanity -= amount;
            if(sanity<0) sanity = 0;
        }

        
    } else if (operation == '+') {        // Increase the stat
        if (stat == "hp") {
            hp += amount;
            if(hp>hpmax) hp = hpmax;

        } else if (stat == "sa") {
            sanity += amount;
            if(sanity>sanity_max) sanity = sanity_max;
        }
    }
}


bool player::CheckIfdied(){
    if(hp == 0 || sanity == 0){
        return true;
    }else return false;
}