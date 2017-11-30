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


bool playerAction(unsigned short k)
{
    switch (k)
    {
    case 'w':
    case 0xE04B: // [LEFT ARROW]
    case 'a':
    case 0xE048: //[UP ARROW]
    case 's':
    case 0xE050: // [DOWN ARROW]
    case 'd':
    case 0xE04D: // [RIGHT ARROW]
        return Player::movechar(k);
        break;
    case ' ':
        Cursor::enable();
        cout << string(50,'\n'); //system("CLS");
        testPrintRoom(Cursor::getRoom().grid);
        return false;
        break;
    case '\\':
        return false;
        break;
    default:
        break;
    }
    return true;
}


bool cursorAction(unsigned short k)
{
    switch (k)
    {
    case 'w':
    case 0xE04B: // [LEFT ARROW]
    case 'a':
    case 0xE048: //[UP ARROW]
    case 's':
    case 0xE050: // [DOWN ARROW]
    case 'd':
    case 0xE04D: // [RIGHT ARROW]
        return Cursor::movechar(k);
        break;
    case ' ':
        Cursor::attack();
        Cursor::disable();
        cout << string(50,'\n'); //system("CLS");
        testPrintRoom(Player::getRoom().grid);
        return false;
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
    cout << string(50,'\n'); //system("CLS");
    testPrintRoom(gameRoom.grid);
    while(true)
    {

        unsigned short key = getKey();

        if (key == 'f') { testFlood(); continue;} // REMOVE THIS LATER!
        if (key == 'g') { generateRoom(); continue;} // REMOVE THIS LATER!

        if(key == '\\' || key == 0x001B){break;}
        else if (!Cursor::isEnabled())
        {
            if(!playerAction(key)) {continue;}
            cout << string(50,'\n'); //system("CLS");
            testPrintRoom(Player::getRoom().grid);
            //cursorInfo();
        }
        else if (Cursor::isEnabled())
        {
            if(!cursorAction(key)) {continue;}
            cout << string(50,'\n'); //system("CLS");
            testPrintRoom(Cursor::getRoom().grid);
        }
    }
    cout << string(50,'\n'); //system("CLS");
    cout << "Game Over\n"; // gameOver()
    cout << "\nPlay Again? (Y/N)\n";
    short key = getKey();
    if(key == 'y') {startGame();}
}
