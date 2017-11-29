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

const char MAPSIZE = 16;
const char PATH = '_';
const char WALL = 178;
const char ENTRANCE = '@';
const char EXIT = '@';
const char PLAYER = 'i';
const char CURSOR = 219;
const char ENEMY = '&';

struct Position;
class Player;
class Enemy;
struct Room;
struct Floor;


struct Position{
    int x;
    int y;
};

class Player{
public:
    static void setRoom(Room & startRoom);
    static Position getPos();
    static Room getRoom();
    static bool movechar(short dir);
    static void takeDamage(double damage);
private:
    static double _health;
    static Position _position;
    static Room * _room;
    //...
};


class Cursor{
public:
    static void setRoom(Room & startRoom);
    static bool isEnabled();
    static Position getPos();
    static Room getRoom();
    static bool movechar(short dir);
private:
    static bool _enabled;
    static Position _position;
    static Room * _room;
    //...
};


struct Enemy{ //turn to class, make identical to player for now
    double health;
    Position pos;
    //...
};




struct Room{
    vector<vector<unsigned char>> grid;
    vector<vector<short>> flood;
    vector<int> exits;
    vector<Enemy> enemies;
    //...
};




struct Floor{
	vector< vector<Room> > rooms;
	int depth;
	//...
};




#endif // STRUCTS_H
