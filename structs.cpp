#include "structs.hpp"

double Player::_health = 100.0;
Position Player::_position = {0,0};
vector<vector<unsigned char>> Player::_roomgrid = {};

Player::Player (vector<vector<unsigned char>> startRoom)
{
    _roomgrid = startRoom;
}

bool Player::movechar(int dir)
{
    switch(dir){
        case 'w': // North
            if(_position.y < MAPSIZE && _roomgrid[_position.x][_position.y+1] == PATH)
            {
                _roomgrid[_position.x][_position.y] = PATH;
                _position.y += _position.y;
                _roomgrid[_position.x][_position.y] = PLAYER;
            }
            break;
        case 's': //South
            if(_position.y <MAPSIZE && _roomgrid[_position.x][_position.y+1] == PATH)
            {
                _roomgrid[_position.x][_position.y] = PATH;
                _position.y -=_position.y;
                _roomgrid[_position.x][_position.y] = PLAYER;
            }
            break;
        case 'd': //East
            if(_position.x <MAPSIZE && _roomgrid[_position.y][_position.x+1] == PATH)
            {
                _roomgrid[_position.y][_position.x] = PATH;
                _position.x +=_position.x;
                _roomgrid[_position.y][_position.x] = PLAYER;

            }
            break;
        case 'a': //West
            if(_position.x <MAPSIZE && _roomgrid[_position.y][_position.x+1] == PATH)
            {
                _roomgrid[_position.y][_position.x] = PATH;
                _position.x -=_position.x;
                _roomgrid[_position.y][_position.x] = PLAYER;

            }
            break;
            return true; // if player or enemy successfully moves to new spot
    }
    return true;
}

void Player::takeDamage(double damage)
{
    _health -= damage;
}






bool Cursor::_enabled = false;
Position Cursor::_position = {0,0};
vector<vector<unsigned char>> Cursor::_roomgrid = {};

Cursor::Cursor (vector<vector<unsigned char>> startRoom)
{
    _roomgrid = startRoom;
}

bool Cursor::isEnabled()
{
    return _enabled;
}

Position Cursor::getPos()
{
    return _position;
}

bool Cursor::movechar(int dir)
{
    switch(dir){
        case 'w': // North
            if(_position.y < MAPSIZE && _roomgrid[_position.x][_position.y+1] == PATH)
            {
                _roomgrid[_position.x][_position.y] = PATH;
                _position.y += _position.y;
                _roomgrid[_position.x][_position.y] = CURSOR;
            }
            break;
        case 's': //South
            if(_position.y <MAPSIZE && _roomgrid[_position.x][_position.y+1] == PATH)
            {
                _roomgrid[_position.x][_position.y] = PATH;
                _position.y -=_position.y;
                _roomgrid[_position.x][_position.y] = CURSOR;
            }
            break;
        case 'd': //East
            if(_position.x <MAPSIZE && _roomgrid[_position.y][_position.x+1] == PATH)
            {
                _roomgrid[_position.y][_position.x] = PATH;
                _position.x +=_position.x;
                _roomgrid[_position.y][_position.x] = CURSOR;

            }
            break;
        case 'a': //West
            if(_position.x <MAPSIZE && _roomgrid[_position.y][_position.x+1] == PATH)
            {
                _roomgrid[_position.y][_position.x] = PATH;
                _position.x -=_position.x;
                _roomgrid[_position.y][_position.x] = CURSOR;

            }
            break;
            return true; // if player or enemy successfully moves to new spot
    }
    return true;
}
