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

#ifdef _WIN32

const char MAPSIZE = 16;
const char PATH = ' ';
const char WALL = 178;
const char ENTRANCE = '@';
const char EXIT = '@';
const char PLAYER = 'i';
const char CURSOR = 'X';
const char ENEMY = '&';

#endif //_WIN32
#ifdef __MACH__

const char MAPSIZE = 16;
const char PATH = ' ';
const char WALL = '#';
const char ENTRANCE = '@';
const char EXIT = '@';
const char PLAYER = 'i';
const char CURSOR = 'X';
const char ENEMY = '&';

#endif //__MACH__


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
    static bool movechar(unsigned short dir);
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
    static void setPos(Position newpos);
    static bool isEnabled();
    static void enable();
    static void disable();
    static Position getPos();
    static Room getRoom();
    static bool movechar(unsigned short dir);
private:
    static bool _enabled;
    static Position _position;
    static Room * _roompoint;
    static Room _room;
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
