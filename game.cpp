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
#include "structs.hpp"
#include "game.hpp"
#include "input.hpp"
#include "intelligence.hpp"
#include "makeMap.hpp"
#include "graphics.hpp"

Floor currentFloor;


bool startGame()
{
    clearScreen();
    cout << "Loading.";
    testMakeFloor({0,0},{MAPSIZE,MAPSIZE},currentFloor);
    cout << ".";
    Player::setRoom(currentFloor.rooms[0][0]);
    Cursor::setRoom(currentFloor.rooms[0][0]);
    Player::setPos({MAPSIZE/2,MAPSIZE/2});
    currentFloor.rooms[0][0].grid[Player::getPos().x][Player::getPos().y] = PLAYER;
    cout << ".";
    clearScreen();
    printRoom(currentFloor.rooms[0][0].grid);
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
    while(true)
    {
        unsigned short key = getKey();

        //if (key == 'f') { testFlood(); continue;} // REMOVE THIS LATER!
        //if (key == 'g') { generateRoom(); continue;} // REMOVE THIS LATER!

        if(key == '\\' || key == 0x001B){break;}
        else if (!Cursor::isEnabled())
        {
            if(!playerAction(key)) {continue;}
            Room currentRoom = Player::getRoom();
            if(currentRoom.grid[Player::getPos().x][Player::getPos().y] == STAIRS) {return true;}
            for(Door d : Player::getRoom().doors)
            {
                if(Player::getPos().x == d.pos.x && Player::getPos().y == d.pos.y)
                {
                    Player::setRoom(currentFloor.rooms[d.nextRoom.x][d.nextRoom.y]);
                    Cursor::setRoom(currentFloor.rooms[d.nextRoom.x][d.nextRoom.y]);
                    Player::setPos({MAPSIZE/2,MAPSIZE/2});
                    Player::setRoomPos(d.nextRoom);
                    currentFloor.rooms[d.nextRoom.x][d.nextRoom.y].grid[Player::getPos().x][Player::getPos().y] = PLAYER;
                    break;
                }
            }
            enemyTurn(currentFloor.rooms[Player::getRoomPos().x][Player::getRoomPos().y]);
            if(Player::getHealth() <= 0) {return false;}
            clearScreen();
            printRoom(Player::getRoom().grid);
            //cursorInfo();
        }
        else if (Cursor::isEnabled())
        {
            if(!cursorAction(key))
            {
                enemyTurn(currentFloor.rooms[Player::getRoomPos().x][Player::getRoomPos().y]);
                Cursor::updateRoom();
            }
            clearScreen();
            printRoom(Cursor::getRoom().grid);
        }
    }
    return false; // QUIT
}
