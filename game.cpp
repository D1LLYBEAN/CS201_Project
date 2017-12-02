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
#include "graphics.hpp"


bool startGame()
{
    clearScreen();
    cout << "Loading.";
    // generateMaps() here
    cout << ".";
    //Player::setPos({0,0});
    cout << ".";
    // printRoom() here
    return game();
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
        clearScreen();
        printRoom(Cursor::getRoom().grid);
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


bool game()
{
    Room gameRoom;
    Floor testFloor;
    makeFloor({0,0},{MAPSIZE,MAPSIZE},testFloor);
    gameRoom = testFloor.rooms[0][0];
    //shittyPopulateMap({0,0},{MAPSIZE-1,MAPSIZE-1},gameRoom);
    gameRoom.grid[Player::getPos().x][Player::getPos().y] = PLAYER;
    Player::setRoom(gameRoom);
    Cursor::setRoom(gameRoom);
    Player::setPos({gameRoom.exits[0].x, gameRoom.exits[0].y});
    clearScreen();
    printRoom(gameRoom.grid);
    while(true)
    {
        unsigned short key = getKey();

        if (key == 'f') { testFlood(); continue;} // REMOVE THIS LATER!
        if (key == 'g') { generateRoom(); continue;} // REMOVE THIS LATER!

        if(key == '\\' || key == 0x001B){break;}
        else if (!Cursor::isEnabled())
        {
            if(!playerAction(key)) {continue;}
            Room currentRoom = Player::getRoom();
            if(Player::getHealth() <= 0) {return false;}
            if(currentRoom.grid[Player::getPos().x][Player::getPos().y] == STAIRS) {return true;}
            else if(Player::getPos().x == currentRoom.exits[0].x && Player::getPos().y == currentRoom.exits[0].y){}//nextRoom(0);} // NEXT LEVEL
            else if(Player::getPos().x == currentRoom.exits[1].x && Player::getPos().y == currentRoom.exits[1].y){}//nextRoom(1);} // PREVIOUS LEVEL
            else if(Player::getPos().x == currentRoom.exits[2].x && Player::getPos().y == currentRoom.exits[2].y){}//nextRoom(2);} // PREVIOUS LEVEL
            else if(Player::getPos().x == currentRoom.exits[3].x && Player::getPos().y == currentRoom.exits[3].y){}//nextRoom(3);} // PREVIOUS LEVEL

            enemyTurn(gameRoom);
            clearScreen();
            printRoom(Player::getRoom().grid);
            //cursorInfo();
        }
        else if (Cursor::isEnabled())
        {
            if(!cursorAction(key))
            {
                enemyTurn(gameRoom);
                clearScreen();
                printRoom(Player::getRoom().grid);
                continue;
            }
            clearScreen();
            printRoom(Cursor::getRoom().grid);
        }
    }
    return false; // QUIT
}
