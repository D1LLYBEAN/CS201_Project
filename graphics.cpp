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
using std::stringstream;
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
    stringstream pHealth;
    pHealth << Player::getHealth();
    stringstream pMaxHealth;
    pMaxHealth << Player::getMaxHealth();
    stringstream pDefense;
    pDefense << Player::getDefense();






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
//    outputString += "HEALTH: " + pHealth.str() + "\n";
    outputString += "Player: \n";
    outputString += "Health: " + pHealth.str() + "\n";
    outputString += "Max Health: " + pMaxHealth.str() + "\n";
    outputString += "Defense : " + pDefense.str() + "\n";

    if(Cursor::isEnabled())
    {
        outputString += "Cursor: ";
        switch(Player::getRoom().grid[Cursor::getPos().x][Cursor::getPos().y]) // get character on grid at cursor position
        {
            case PLAYER:
                outputString += "Player\n";
                break;
            case ENEMY:
                for(unsigned int i=0; i < Player::getRoom().enemies.size(); i++) // find enemy in room vector
                {
                    if(Player::getRoom().enemies[i].getPos().x == Cursor::getPos().x && Player::getRoom().enemies[i].getPos().y == Cursor::getPos().y) // if true, this is the enemy at the cursor position
                    {
                        stringstream eHealth;
                        eHealth << Player::getRoom().enemies[i].getHealth();
                        stringstream ePower;
                        ePower << Player::getRoom().enemies[i].getPower();
                        stringstream eDefense;
                        eDefense << Player::getRoom().enemies[i].getDefense();

                        outputString += "Enemy \n";
                        outputString += "Health: "+ eHealth.str() + "\n";
                        outputString += "Power: " + ePower.str() + "\n";
                        outputString += "Defense: " + eDefense.str() + "\n";
                    }
                }
                break;
            case WALL:
                outputString += "Wall \n";
                break;
            case DOOR:
                outputString += "Door \n";
                break;
            case STAIRS:
                outputString += "Hole to next floor \n";
                break;
            default:
                break;
        }
    }

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
