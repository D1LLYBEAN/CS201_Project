#include <iostream>
#include "structs.hpp"
#include "game.hpp"
#include <math.h>
#include <stdlib.h>
#include "intelligence.hpp"
#include "graphics.hpp"

// ---------- Player ---------- //

double Player::_health = 100.0;
Position Player::_position = {MAPSIZE/2,MAPSIZE/2};
Room * Player::_room = nullptr;
Floor * Player::_floor = nullptr;
double Player::_power = 50.0;

void Player::setFloor(Floor & startFloor) // may need this for cursor too...
{
	_floor = &startFloor;
}

Floor Player::getFloor() // same here - liam
{
    return (*_floor);
}

void Player::setRoom (Room & startRoom)
{
    _room = &startRoom;
}

Position Player::getPos()
{
    return _position;
}

void Player::setPos(Position newPos)
{
    _position = newPos;
}

Room Player::getRoom()
{
    return (*_room);
}

bool Player::movechar(unsigned short dir)
{
    switch(dir){
        case 'w': // North
        case 0xE048: //[UP ARROW]
            if(_position.y < MAPSIZE-1 && ((*_room).grid[_position.x][_position.y+1] == PATH|| (*_room).grid[_position.x][_position.y+1] == EXIT))
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.y++;
                (*_room).grid[_position.x][_position.y] = PLAYER;
            }
            else{return false;}
            break;
        case 's': //South
        case 0xE050: // [DOWN ARROW]
            if(_position.y > 0 && ((*_room).grid[_position.x][_position.y-1] == PATH|| (*_room).grid[_position.x][_position.y-1] == EXIT))
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.y--;
                (*_room).grid[_position.x][_position.y] = PLAYER;
            }
            else{return false;}
            break;
        case 'd': //East
        case 0xE04D: // [RIGHT ARROW]
            if(_position.x < MAPSIZE-1 && ((*_room).grid[_position.x+1][_position.y] == PATH || (*_room).grid[_position.x+1][_position.y] == EXIT))
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.x++;
                (*_room).grid[_position.x][_position.y] = PLAYER;
            }
            else{return false;}
            break;
        case 'a': //West
        case 0xE04B: // [LEFT ARROW]
            if(_position.x > 0 && ((*_room).grid[_position.x-1][_position.y] == PATH || (*_room).grid[_position.x-1][_position.y] == EXIT))
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.x--;
                (*_room).grid[_position.x][_position.y] = PLAYER;
            }
            else{return false;}
            break;
    }
    return true;
}

void Player::takeDamage(double damage)
{
    _health -= damage;
}

double Player::getHealth()
{
    return _health;
}

double Player::getPower()
{
    return _power;
}

// ---------- Cursor ---------- //

bool Cursor::_enabled = false;
Position Cursor::_position = {0,0};
Room * Cursor::_roompoint = nullptr;
Room Cursor::_room = {};

void Cursor::setRoom (Room & newRoom)
{
    _roompoint = &newRoom;
}

void Cursor::setPos (Position newpos)
{
    _position = newpos;
}

bool Cursor::isEnabled()
{
    return _enabled;
}

void Cursor::enable()
{
    _enabled = true;
    _position = Player::getPos();
    _room = (*_roompoint);
    _room.grid[_position.x][_position.y] = CURSOR;
}

void Cursor::disable()
{
    _enabled = false;
}

Position Cursor::getPos()
{
    return _position;
}

Room Cursor::getRoom()
{
    return _room;
}

bool Cursor::movechar(unsigned short dir)
{
    switch(dir){
        case 'w': // North
        case 0xE048: //[UP ARROW]
            if(_position.y < MAPSIZE-1)// && _room.grid[_position.x][_position.y+1] == PATH)
            {
                _room.grid[_position.x][_position.y] = (*_roompoint).grid[_position.x][_position.y];
                _position.y++;
                _room.grid[_position.x][_position.y] = CURSOR;
            }
            else{return false;}
            break;
        case 's': //South
        case 0xE050: // [DOWN ARROW]
            if(_position.y > 0)// && _room.grid[_position.x][_position.y-1] == PATH)
            {
                _room.grid[_position.x][_position.y] = (*_roompoint).grid[_position.x][_position.y];
                _position.y--;
                _room.grid[_position.x][_position.y] = CURSOR;
            }
            else{return false;}
            break;
        case 'd': //East
        case 0xE04D: // [RIGHT ARROW]
            if(_position.x < MAPSIZE-1)// && _room.grid[_position.x+1][_position.y] == PATH)
            {
                _room.grid[_position.x][_position.y] = (*_roompoint).grid[_position.x][_position.y];
                _position.x++;
                _room.grid[_position.x][_position.y] = CURSOR;
            }
            else{return false;}
            break;
        case 'a': //West
        case 0xE04B: // [LEFT ARROW]
            if(_position.x > 0)// && _room.grid[_position.x-1][_position.y] == PATH)
            {
                _room.grid[_position.x][_position.y] = (*_roompoint).grid[_position.x][_position.y];
                _position.x--;
                _room.grid[_position.x][_position.y] = CURSOR;
            }
            else{return false;}
            break;
    }
    return true;
}

void Cursor::attack()
{
    int x1 = Player::getPos().x;
    int y1 = Player::getPos().y;
    int x2 = _position.x;
    int y2 = _position.y;
    double length = std::max(abs(x2-x1), abs(y2-y1));
    int x = 0;
    int y = 0;
    for(int i=0; i <= length; i++)
    {
        // interpolate between (x1,y1) and (x2,y2)
        double t = double(i)/length;
        // at t=0.0 we get (x1,y1); at t=1.0 we get (x2,y2)
        if ((*_roompoint).grid[round(x1 * (1.0-t) + x2 * t)][y] == WALL && (*_roompoint).grid[x][round(y1 * (1.0-t) + y2 * t)] == WALL)
        {
            std::cout << "HIT WALL @ (" << x << "," << y << ")\n";
            break;
        }
        else
        {
            x = round(x1 * (1.0-t) + x2 * t);
            y = round(y1 * (1.0-t) + y2 * t);
        }
        // now check tile (x,y)
        if((*_roompoint).grid[x][y] == WALL)
        {
            std::cout << "HIT WALL @ (" << x << "," << y << ")\n";
            break;
        }
        else if((*_roompoint).grid[x][y] == ENEMY)
        {
            std::cout << "HIT ENEMY @ (" << x << "," << y << ")\n";
            for(unsigned int i=0; i < (*_roompoint).enemies.size(); i++)
            {
                if((*_roompoint).enemies[i].getPos().x == x && (*_roompoint).enemies[i].getPos().y == y)
                {
                    if(!(*_roompoint).enemies[i].takeDamage(Player::getPower())) // if the enemy is no longer alive...
                    {
                        (*_roompoint).grid[x][y] = PATH;
                        (*_roompoint).enemies.erase((*_roompoint).enemies.begin() + i);
                    }
                }
            }
            break;
        }
        else
        {
            _room.grid[x][y] = '+';
        }
    }
    printRoom(_room.grid);
    // don't move game forward if player doesn't try to attack?
}
