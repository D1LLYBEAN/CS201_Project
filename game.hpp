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
// Core game header.


#include "structs.hpp"

void startGame();
bool playerAction(short);
void game();


class Cursor
{
public:
    bool isEnabled(){return _enabled;}
    Position getPos(){return _pos;}
    bool move(int dir)
    {
        //same as player.moveChar and enemy.moveChar
        return false;
    }
private:
    bool _enabled;
    Position _pos;
};
