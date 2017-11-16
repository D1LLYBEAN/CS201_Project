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
// Core game.

// Standard Libraries
#include <iostream>
using std::cout;
#include <stdlib.h>
// User Libraries
//#include "makeMap.hpp"
#include "game.hpp"


void startGame()
{
    system("CLS");
    cout << "Loading.";
    // generateMaps() here
    cout << ".";
    //...
    cout << ".";
    // printRoom() here
    game();
}

void game()
{
    while(true)
    {
        //...
        if(true){break;}
    }
    system("CLS");
    cout << "Game Over"; // gameOver()
}
