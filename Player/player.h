
#include <iostream>
#include <windows.h>    //for SetConsoleCursorPosition

class player{
        double hp = 100;
        double hpmax = 100;
        double sanity = 100;
        double sanity_max = 100;
    public:
        void printstats();
        void changestat(std::string change);           //use keyword "hp" or "sa" example:hp-1
};

void movecursor(int,int);
int currentcursor(char);

