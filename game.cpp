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
#include "makeMap.hpp"


void startGame()
{
    cout << string(50,'\n'); //system("CLS");
    cout << "Loading.";
    // generateMaps() here
    cout << ".";
    Player player1;
    Cursor cursor1;
    cout << ".";
    // printRoom() here
    cout << string(50,'\n'); //system("CLS");
    cout << "Enter \'\\\' to end game!\n";
    cout << "Assign other hotkeys in game.cpp, within game(), for testing purposes!\n";
    cout << "[Dillon] I am using the \'f\' key to test my flood algorithm.\n";
    cout << "[Liam] I am using the 'g' key for testing floor/room generation.\n";
    cout << "Try to limit hotkeys to one-per-person, so we don't all keep editing game.cpp.\n";
    cout << "Make a function and edit it within your .cpp instead of editing game.cpp.\n";
    game();
}


bool playerAction(short k)
{
    switch (k)
    {
    case 'w':
        //player.move(0);
        break;
    case 'a':
        //player.move(1);
        break;
    case 's':
        //player.move(2);
        break;
    case 'd':
        //player.move(3);
        break;
    case ' ':
        //cursor(player1);
        break;
    case '\\':
        return false;
        break;
    default:
        break;
    }
    return true;
}


bool cursorAction(short k)
{
    switch (k)
    {
    case 'w':
        //cursor.move(0);
        break;
    case 'a':
        //cursor.move(1);
        break;
    case 's':
        //cursor.move(2);
        break;
    case 'd':
        //cursor.move(3);
        break;
    case ' ':
        //attack(player1,cursor.pos);
        break;
    case '\\':
        return false;
        break;
    default:
        break;
    }
    return true;
}


void game()
{
    while(true)
    {
        short key = getKey();

        if (!cursor.isEnabled() && !playerAction(key)) {break;}
        if (cursor.isEnabled() && !cursorAction(key)) {break;}

        else if (key == 'f') { testFlood(); } // REMOVE THIS LATER!
        else if (key == 'g') { generateRoom(); } // REMOVE THIS LATER!
        // ASSIGN MORE HOTKEYS HERE FOR TESTING!

        //...
    }
    cout << string(50,'\n'); //system("CLS");
    cout << "Game Over\n"; // gameOver()
    cout << "\nPlay Again? (Y/N)\n";
    short key = getkey();
    if(key == 'y') {startGame();}
}
