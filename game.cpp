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
    makeFloor({0,0},{MAPSIZE,MAPSIZE},currentFloor);
    cout << ".";
    Player::setRoom(currentFloor.rooms[0][0]);
    Cursor::setRoom(currentFloor.rooms[0][0]);
    Player::setPos({MAPSIZE/2,MAPSIZE/2});
    Player::setRoomPos({0,0});
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
        //if (key == 'g') { printFloor(Player::getFloor()); continue;} // REMOVE THIS LATER!

        if(key == '\\' || key == 0x001B){break;}
        else if (!Cursor::isEnabled())
        {
            if(!playerAction(key)) {continue;}
            Room currentRoom = Player::getRoom();
            if(Player::getPos().x == currentRoom.stairs.x && Player::getPos().y == currentRoom.stairs.y)  // need to finish stair use
            {
                Player::setMaxHealth(Player::getMaxHealth() + 5.0);
                Player::setDefense(Player::getDefense() + 0.5);
                Player::setHealth(Player::getMaxHealth());
                currentFloor.depth++;
                return true;
            }
            for(Door d : currentRoom.doors)
            {
                if(Player::getPos().x == d.pos.x && Player::getPos().y == d.pos.y)
                {
                    currentFloor.rooms[Player::getRoomPos().x][Player::getRoomPos().y].grid[d.pos.x][d.pos.y] = DOOR;
                    Player::setRoom(currentFloor.rooms[d.nextRoom.x][d.nextRoom.y]);
                    Cursor::setRoom(currentFloor.rooms[d.nextRoom.x][d.nextRoom.y]);
                    if(Player::getPos().y == MAPSIZE-1)//NORTH
                    {
                    	currentRoom.grid[Player::getPos().x][Player::getPos().y] = DOOR;//DNW
                    	Player::setPos({d.pos.x,MAPSIZE-1-d.pos.y});
					}
					else if(Player::getPos().x == MAPSIZE-1)//EAST
					{
						currentRoom.grid[Player::getPos().x][Player::getPos().y] = DOOR;//DNW
						Player::setPos({MAPSIZE-1-d.pos.x,d.pos.y});
					}
					else if(Player::getPos().y == 0)//SOUTH
					{
						currentRoom.grid[Player::getPos().x][Player::getPos().y] = DOOR;//DNW
						Player::setPos({d.pos.x,d.pos.y+MAPSIZE-1});
					}
					else//WEST
					{
						currentRoom.grid[Player::getPos().x][Player::getPos().y] = DOOR;//DNW
						Player::setPos({d.pos.x+MAPSIZE-1,d.pos.y});
					}
                    Player::setRoomPos(d.nextRoom);
                    currentFloor.rooms[d.nextRoom.x][d.nextRoom.y].grid[Player::getPos().x][Player::getPos().y] = PLAYER;
                    break;
                }
            }
            enemyTurn(currentFloor.rooms[Player::getRoomPos().x][Player::getRoomPos().y]);
            clearScreen();
            printRoom(Player::getRoom().grid);
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
        if(Player::getHealth() <= 0) {return false;}
    }
    return false; // QUIT
}
