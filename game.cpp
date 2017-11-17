// game.cpp
//
// CS201_Project
// Videogame
//
// Team:
// Grace Bolt
// Liam Eberhart
// Dillon Mills
//
// Core game.

// Standard Libraries
#include <iostream>
using std::cout;
//#include <stdlib.h>
// Custom Libraries
//#include "makeMap.hpp"
#include "game.hpp"
#include "input.hpp"
#include "intelligence.hpp"


void startGame()
{
    cout << string(50,'\n'); //system("CLS");
    cout << "Loading.";
    // generateMaps() here
    cout << ".";
    //...
    cout << ".";
    // printRoom() here
    cout << string(50,'\n'); //system("CLS");
    cout << "Enter \'\\\' to end game!\n";
    cout << "Assign other hotkeys in game.cpp, within game(), for testing purposes!\n";
    cout << "[Dillon] I am using the \'f\' key to test my flood algorithm.\n";
    cout << "Try to limit hotkeys to one-per-person, so we don't all keep editing game.cpp.\n";
    cout << "Make a function and edit it within your .cpp instead of editing game.cpp.\n";
    game();
}

void game()
{
    while(true)
    {
        short key = getKey();
        //if (key == 0x001B) {break;} // keyMap["ESC"]
        if (key == '\\') {break;}
        else if (key == 'f') { testFlood(); }
        // ASSIGN MORE HOTKEYS HERE FOR TESTING!

        //...
    }
    cout << string(50,'\n'); //system("CLS");
    cout << "Game Over"; // gameOver()
}
