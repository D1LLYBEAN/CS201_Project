#include <iostream>
#include "structs.hpp"

// ---------- Player ---------- //

double Player::_health = 100.0;
Position Player::_position = {0,0};
Room * Player::_room = nullptr;

void Player::setRoom (Room & startRoom)
{
    _room = &startRoom;
}

Position Player::getPos()
{
    return _position;
}

Room Player::getRoom()
{
    return (*_room);
}

bool Player::movechar(short dir)
{
    switch(dir){
        case 'w': // North
            if(_position.y < MAPSIZE && (*_room).grid[_position.x][_position.y+1] == PATH)
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.y++;
                (*_room).grid[_position.x][_position.y] = PLAYER;
            }
            else{return false;}
            break;
        case 's': //South
            if(_position.y > 0 && (*_room).grid[_position.x][_position.y-1] == PATH)
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.y--;
                (*_room).grid[_position.x][_position.y] = PLAYER;
            }
            else{return false;}
            break;
        case 'd': //East
            if(_position.x < MAPSIZE && (*_room).grid[_position.x+1][_position.y] == PATH)
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.x++;
                (*_room).grid[_position.x][_position.y] = PLAYER;
            }
            else{return false;}
            break;
        case 'a': //West
            if(_position.x > 0 && (*_room).grid[_position.x-1][_position.y] == PATH)
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

// ---------- Cursor ---------- //

bool Cursor::_enabled = false;
Position Cursor::_position = {0,0};
Room * Cursor::_room = nullptr;

void Cursor::setRoom (Room & startRoom)
{
    _room = &startRoom;
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
    return (*_room);
}

bool Cursor::movechar(short dir)
{
    switch(dir){
        case 'w': // North
            if(_position.y < MAPSIZE && (*_room).grid[_position.x][_position.y+1] == PATH)
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.y++;
                (*_room).grid[_position.x][_position.y] = CURSOR;
            }
            else{return false;}
            break;
        case 's': //South
            if(_position.y > 0 && (*_room).grid[_position.x][_position.y-1] == PATH)
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.y--;
                (*_room).grid[_position.x][_position.y] = CURSOR;
            }
            else{return false;}
            break;
        case 'd': //East
            if(_position.x < MAPSIZE && (*_room).grid[_position.x+1][_position.y] == PATH)
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.x++;
                (*_room).grid[_position.x][_position.y] = CURSOR;
            }
            else{return false;}
            break;
        case 'a': //West
            if(_position.x > 0 && (*_room).grid[_position.x-1][_position.y] == PATH)
            {
                (*_room).grid[_position.x][_position.y] = PATH;
                _position.x--;
                (*_room).grid[_position.x][_position.y] = CURSOR;
            }
            else{return false;}
            break;
    }
    return true;
}
