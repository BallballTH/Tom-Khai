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
    int bar1 = 176; int bar2 = 219;
    
    SetConsoleCP(437);         // for bar text
    SetConsoleOutputCP(43);

    int tempX = currentcursor('x');      // Get Current position for pirnt Sanity bar

    //printHP
    movecursor(20);
    std::cout << "HP: ";
    for(int i=0; i<20; i++){
        std::cout << char(bar1);
    }
    movecursor(-20);
    for(int i=0; i<percent_hp*20; i++){
        std::cout << char(bar2);
    }

    std::cout<<"\r";                   // move cursor back to start
    //printSanity

    movecursor(tempX+50);
    std::cout << "SA: ";
    for(int i=0; i<20; i++){
        std::cout << char(bar1);
    }
    movecursor(-20);
    for(int i=0; i<percent_sa*20; i++){
        std::cout << char(bar2);
    }

    std::cout<<"\n------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void player::changestat(const std::string& change) {
    char text[50];
    double amount;
    char operation;

    sscanf(change.c_str(), "%[^-+ ] %c %lf", text, &operation, &amount);
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

