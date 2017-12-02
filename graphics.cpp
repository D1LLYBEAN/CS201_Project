// mechanics.cpp
//
// CS201_Project
// Videogame
//
// Team:
// Grace Bolt
// Liam Eberhart
// Dillon Mills
//
// Terminal output functions

#include "graphics.hpp"
#include "structs.hpp"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <sstream>
using std::istringstream;
#include <vector>
using std::vector;
#include <stdlib.h>

void startScreen()
{
    cout << "Font: Courier New (20 pt)\n";
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
}

void printRoom(vector<vector<unsigned char>> pRoom)
{
    std::stringstream pHealth;
    pHealth << Player::getHealth();
    
    string outputString = "";
    outputString += string(MAPSIZE+2,WALL) + "\n" + string(1,WALL);
    for(int i=MAPSIZE-1; i>=0; i--)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            outputString += pRoom[j][i];
        }
        outputString += string(1,WALL) + "\n" + string(1,WALL);
    }
    outputString += string(MAPSIZE+1,WALL) + "\n";
    outputString += "HEALTH: " + pHealth.str() + "\n";
    
    cout << outputString;
}

//for windows
#ifdef _WIN32

void clearScreen()
{
    system("CLS");
}

#endif // WIN32

//for mach
#ifdef __MACH__

void clearScreen()
{
    cout << string(50,'\n');
}


#endif
