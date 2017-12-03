// intelligence.cpp
//
// CS201_Project
// Videogame
//
// Team:
// Grace Bolt
// Liam Eberhart
// Dillon Mills
//
// Controls enemy characters (header)


#include<vector>
#include "structs.hpp"

void enemyLogic(Enemy & e, Room & r);
void enemyTurn(Room & r);
void spawnEnemies(Room & r, int eCount);
void flood(Position pPos, Room & room);
void testFlood();
void testPrintFlood(std::vector<std::vector<short>> printMap);
void testmakeRoom(Position entr, Position exit, Room & r);
void testMakeFloor(Position entr, Position exit, Floor & f);
