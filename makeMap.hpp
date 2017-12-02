//makeMap.hpp
//
// CS201_Project
// Videogame
//
// Team:
// Grace Bolt
// Liam Eberhart
// Dillon Mills
//
// creates the map

#include<vector>
using std::vector;

#include "structs.hpp"

void floodFill(Position zero, Room & room);
Room makeRoom(Position entr, Position exit, Room & r);
void showRoom(vector<vector<unsigned char>> printRoom);
void generateRoom();
void printFloor(Floor f);
void makeFloor(Position entr, Position exit, Floor & f);
void nextRoom(int dir);
