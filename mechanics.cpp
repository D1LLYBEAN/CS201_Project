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

//#include "mechanics.hpp"
//#include "structs.hpp"

// moves player or enemy one grid space
// requires "target" grid space to be open
// depends on input direction (Up/Down/Left/Right)
// updates player/enemy struct, and updates grid vector
//bool moveChar(Position pos, int dir)
//{
//    switch(dir){
//        case 'w': // North
//            pos.y += pos.y;
//            break;
//        case 's': //South
//            pos.y -= pos.y;
//            break;
//        case 'd': //East
//            pos.x += pos.x;
//            break;
//        case 'a': //West
//            pos.x -= pos.x;
//            break;
//            return true; // if player or enemy successfully moves to new spot
//    }
//    return true;
//}

// applies damage to target
// based on attacker and defender stats?
// I asked Chris and he told me that auto is not allowed in a function prototype.  It must be the type of the passed variable and has something to do with templates.
//void attack(auto attacker, auto defender)
//{
//    defender.health -= 1.0;
//    //defender.health -= attacker.attackpower / defender.armor
//    //...
//}
