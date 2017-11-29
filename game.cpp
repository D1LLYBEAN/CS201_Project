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
#include "structs.hpp"
#include "game.hpp"
#include "input.hpp"
#include "intelligence.hpp"
#include "makeMap.hpp"

Floor FLOOR;


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
    case 'a':
    case 's':
    case 'd':
        return Player::movechar(k);
        break;
    case ' ':
        //Cursor::toggleCursor();
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
    case 'a':
    case 's':
    case 'd':
        return Cursor::movechar(k);
        break;
    case ' ':
        //attack(player1,cursor.pos);
        //Cursor::toggleCursor;
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
    Room gameRoom;
    shittyPopulateMap({0,0},{MAPSIZE-1,MAPSIZE-1},gameRoom);
    gameRoom.grid[Player::getPos().x][Player::getPos().y] = PLAYER;
    Player::setRoom(gameRoom);
    Cursor::setRoom(gameRoom);
    while(true)
    {
        cout << string(50,'\n'); //system("CLS");
        testPrintRoom(gameRoom.grid);
        short key = getKey();

        if (!Cursor::isEnabled() && !playerAction(key)) {break;}
        if (Cursor::isEnabled() && !cursorAction(key)) {break;}

        else if (key == 'f') { testFlood(); } // REMOVE THIS LATER!
        else if (key == 'g') { generateRoom(); } // REMOVE THIS LATER!
        // ASSIGN MORE HOTKEYS HERE FOR TESTING!

        //...
    }
    cout << string(50,'\n'); //system("CLS");
    cout << "Game Over\n"; // gameOver()
    cout << "\nPlay Again? (Y/N)\n";
    short key = getKey();
    if(key == 'y') {startGame();}
}
