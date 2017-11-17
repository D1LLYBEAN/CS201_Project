// mechanics.cpp
//
// CS201_Project
// Videogame
//
// Team:
// Grace Bolt
// Liam Eberhart
// Dillon Mills
//
// Essential gameplay functions

#include "mechanics.hpp"
#include "structs.hpp"

// moves player or enemy one grid space
// requires "target" grid space to be open
// depends on input direction (Up/Down/Left/Right)
// updates player/enemy struct, and updates grid vector
bool moveChar(Position pos, int dir)
{
    switch(dir)
    case 0: // North
    //...
    return true; // if player or enemy successfully moves to new spot
}

// applies damage to target
// based on attacker and defender stats?
void attack(auto attacker, auto defender)
{
    defender.health -= 1.0;
    //defender.health -= attacker.attackpower / defender.armor
    //...
}
