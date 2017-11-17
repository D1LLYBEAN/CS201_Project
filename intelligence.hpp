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

void flood(Position pPos, vector<vector<short>> & floodMap, vector<vector<short>> roomMap);
void testFlood();
void testPrintRoom(vector<vector<char>> printMap);
void testPrintFlood(vector<vector<short>> printMap);
void shittyPopulateMap(vector<vector<char>> & popMap);
