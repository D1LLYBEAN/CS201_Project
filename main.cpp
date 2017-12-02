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
// Custom Libraries
#include "game.hpp"
#include "input.hpp"
#include "graphics.hpp"


int main()
{
    startScreen();

    cout << "\nPress Start\n";
    // This will also need its own input.cpp/.hpp files!
    while (true)
    {
        getKey();
        break;
        //if (key == 0x000D) {break;} // keyMap["ENTER"]
    }

    while(true)
    {
        if(startGame()){continue;} // Next Level
        cout << string(50,'\n'); //system("CLS");
        cout << "Game Over\n"; // gameOver()
        cout << "\nPlay Again? (Y/N)\n";
        short key = getKey();
        if(key == 'y') {continue;}
        else {break;}
    }


    return 0;
}
