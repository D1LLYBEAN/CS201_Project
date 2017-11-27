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


// Standard Libraries
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
//#include <conio.h>      // for getch()
//#include <stdlib.h>     // for System("CLS")
// Custom Libraries
#include "game.hpp"
#include "input.hpp"


int main()
{
    cout << "Font: Courier New (14 pt)\n";
    cout << "Terminal: Width = 80, Height = 40\n";
    string file_path = __FILE__;
    string dir_path = file_path.substr(0, file_path.rfind("\\"));
    string startScreenFile = dir_path + "\\StartScreen.txt";
    cout << startScreenFile << endl;
    // This should be moved to it's own graphics.cpp/.hpp files!
    ifstream iFile(startScreenFile); // needs to be in local project file?
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
        getKey();
        break;
        //if (key == 0x000D) {break;} // keyMap["ENTER"]
    }

    startGame();

    return 0;
}
