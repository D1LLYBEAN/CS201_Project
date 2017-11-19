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
using std::vector;

#include "structs.hpp"

void spawnEnemies(Room & r);
void flood(Position pPos, Room & room);
void testFlood();
void testPrintRoom(vector<vector<unsigned char>> printMap);
void testPrintFlood(vector<vector<short>> printMap);
void shittyPopulateMap(Position entr, Position exit, Room & r);
