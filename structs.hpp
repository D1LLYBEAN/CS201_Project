// structs.hpp
//
// CS201_Project
// Videogame
//
// Team:
// Grace Bolt
// Liam Eberhart
// Dillon Mills
//
// contains important structs


#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
using std::vector;

struct Position{
    int x;
    int y;
};

struct Player{
    double health;
    Position pos;
    //...
};

struct Enemy{
    double health;
    Position pos;
    //...
};

struct Room{
    vector<vector<unsigned char>> grid;
    vector<vector<short>> flood;
    vector<int> exits;
    vector<Enemy> enemies;
    Position pos;
    //...
};
/*
Because the random gen is pseudo random, i could have the floor hold 2d array of keys and then re-gen each time,
Is inefficent.
*/

struct Floor{
	vector< vector<Room> > rooms;
	int depth;
	//...
};


#endif // STRUCTS_H
