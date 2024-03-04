
#include <iostream>
#include <windows.h>    // for SetConsoleCursorPosition
#include <string>       // for string manipulation
#include <fcntl.h>      // for show Unicode on stream (file control in "setmode")
#include <io.h>         // for show Unicode on stream (setmode)


class player{
        double hp = 100;
        double hpmax = 100;
        double sanity = 100;
        double sanity_max = 100;
        bool DeathFlag = false;
    public:
        bool CheckIfdied();
        void printstats();
        void changestat(const std::string& change);                                //use keyword "hp" or "sa" example: "hp-1"
        friend class Game;
};

void movecursor(int,int);
int  currentcursor(char);



