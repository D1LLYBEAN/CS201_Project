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

#include <iostream>
#include <vector>
using std::vector;

const char MAPSIZE = 16;
const char PATH = ' ';
const char WALL = '#';
const char ENTRANCE = '@';
const char EXIT = '@';
const char STAIRS = 'O';
const char PLAYER = 'i';
const char CURSOR = 'X';
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
    static void setFloor(Floor & startFloor); // need this for cursor too? why is cursor not a part of player...
    static Position getPos();
    static void setPos(Position newPos);
    static Room getRoom();
    static Floor getFloor(); // need this for cursor too? why is cursor not a part of player...
    static bool movechar(unsigned short dir);
    static void takeDamage(double damage);
    static double getHealth();
    static double getPower();
private:
    static double _health;
    static Position _position;
    static Room * _room;
    static Floor * _floor;
    static double _power;
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
    static void attack();
private:
    static bool _enabled;
    static Position _position;
    static Room * _roompoint;
    static Room _room;
    //...
};


class Enemy{ //turn to class, make identical to player for now
public:
    Enemy()
    {
        _health = 100.0;
        _position = {0,0};
        _power = 10.0;
    }
    Position getPos()
    {
        return _position;
    }
    void setPos(Position newPos)
    {
        _position = newPos;
    }
    bool takeDamage(double damage)
    {
        _health -= damage;
        if(_health <= 0.0)
        {
            return false;
        }
        return true;
    }
    double getPower()
    {
        return _power;
    }
private:
    double _health;
    Position _position;
    double _power;
};




struct Room{
    vector<vector<unsigned char>> grid;
    vector<vector<short>> flood;
    vector<Position> exits;
    vector<Enemy> enemies;
    Position pos;
    //...
};




struct Floor{
	vector< vector<Room> > rooms;
	int depth;
	//...
};




#endif // STRUCTS_H
