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
const char DOOR = '@';
const char STAIRS = 'O';
const char PLAYER = 'i';
const char CURSOR = '*';
const char ENEMY = 'f';
const char BULLET = '+';

struct Position;
class Player;
class Enemy;
struct Room;
struct Door;
struct Floor;

extern Floor currentFloor;

struct Position{
    int x;
    int y;
};

class Player{
public:
    static void reset();
    static void setRoom(Room & startRoom);
    static void setFloor(Floor & startFloor);
    static Position getPos();
    static void setPos(Position newPos);
    static Room getRoom();
    static void setRoomPos(Position);
    static Position getRoomPos();
    static Floor getFloor();
    static bool movechar(unsigned short dir);
    static void takeDamage(double damage);
    static double getHealth();
    static void setHealth(double newHealth);
    static double getMaxHealth();
    static void setMaxHealth(double newHealth);
    static double getPower();
    static void setPower(double newPower);
    static double getDefense();
    static void setDefense(double newDefense);
private:
    static double _maxHealth;
    static double _health;
    static Position _position;
    static Position _roomPosition;
    static Room * _room;
    static Floor * _floor;
    static double _power;
    static double _defense;
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
    static void updateRoom();
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
        _position = {0,0};
        _health = 10.0;
        _power = 5.0;
        _defense = 1.0;
    }
    Position getPos()
    {
        return _position;
    }
    void setPos(Position newPos)
    {
        _position = newPos;
    }
    void setHealth(double newHealth)
    {
        _health = newHealth;
    }
    double getPower()
    {
        return _power;
    }
    void setPower(double newPower)
    {
        _power = newPower;
    }
    void setDefense(double newDefense)
    {
        _defense = newDefense;
    }
    bool takeDamage(double damage)
    {
        _health -= damage / _defense;
        if(_health <= 0.0)
        {
            Player::setPower(Player::getPower() + 1.0);
            return false;
        }
        return true;
    }
private:
    double _health;
    Position _position;
    double _power;
    double _defense;
};


struct Room{
    vector<vector<unsigned char>> grid;
    vector<vector<short>> flood;
    vector<Door> doors;
    vector<Enemy> enemies;
    Position pos;
    Position stairs;
    //...
};

struct Floor{
	vector< vector<Room> > rooms;
	int depth;
	//...
};


struct Door
{
    Position pos;
    Position nextRoom;
};

bool isDoor(Position pos);

#endif // STRUCTS_H
