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
const char WALL = 219;
const char ENTRANCE = '@';
const char EXIT = '@';
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
    bool move(int dir)
    {
        switch(dir){
            case 'w': // North
                if(_position.y < MAPSIZE && _room.grid[_position.x][_position.y+1] == PATH)
                {
                    _room.grid[_position.x][_position.y] = PATH;
                    _position.y += _position.y;
                    _room.grid[_position.x][_position.y] = PLAYER;
                }
                break;
            case 's': //South
                if(_position.y <MAPSIZE && _room.grid[_position.x][_position.y+1] == PATH)
                {
                    _room.grid[_position.x][_position.y] = PATH;
                    _position.y -=_position.y;
                    _room.grid[_position.x][_position.y] = PLAYER;

                }
                break;
            case 'd': //East
                if(_position.x <MAPSIZE && _room.grid[_position.y][_position.x+1] == PATH)
                {
                    _room.grid[_position.y][_position.x] = PATH;
                    _position.x +=_position.x;
                    _room.grid[_position.y][_position.x] = PLAYER;

                }
                break;
            case 'a': //West
                if(_position.x <MAPSIZE && _room.grid[_position.y][_position.x+1] == PATH)
                {
                    _room.grid[_position.y][_position.x] = PATH;
                    _position.x -=_position.x;
                    _room.grid[_position.y][_position.x] = PLAYER;

                }
                break;
                return true; // if player or enemy successfully moves to new spot
        }
        return true;
    }

    int attack() {

    }
    //...attack function
private:
    double _health;
    Position _position;
    Room & _room;
    //...
};




struct Enemy{ //turn to class, make identical to player for now
    double health;
    Position pos;
    //...
};




class Room{
public:
    vector<vector<unsigned char>> grid;
    vector<vector<short>> flood;
    vector<int> exits;
    vector<Enemy> enemies;
    //...
private:

};




struct Floor{
	vector< vector<Room> > rooms;
	int depth;
	//...
};




#endif // STRUCTS_H
