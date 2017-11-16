// main.cpp
//
// CS201_Project
// Videogame
//
// Team:
// Grace Bolt
// Liam Eberhart
// Dillon Mills
//
// Initializes game.


//Standard Libraries
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <conio.h>      // for getch()
#include <stdlib.h>     // for System("CLS")
//User Libraries
#include "game.hpp"


int main()
{
    // This should be moved to it's own graphics.cpp/.hpp files!
    ifstream iFile("StartScreen.txt"); // needs to be in local project file?
    string lines;
    while (true)
    {
        string fLine;
        getline(iFile,fLine);
        if (!iFile)
        {
            if(EOF)
            {
                break;
            }
        }
        else
        {
            lines += fLine + "\n";
        }
    }
    cout << lines;

    cout << "\nPress Start\n";
    // This will also need its own input.cpp/.hpp files!
    while (true)
    {
        char key = getch();
        if (key == 0x00 || key == 0xE0)
        {
            key *= 0x0100; // shift left by 8 bits to get extended code
            key += getch(); // retrieve second byte of extended code
        }
        if (key == 0x000D) {break;}
    }

    startGame();

    return 0;
}
