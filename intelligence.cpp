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
// Controls enemy characters.

// Standard Libraries
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
using std::string;
// Custom Libraries
#include "intelligence.hpp"
#include "structs.hpp"
#include "input.hpp"
//#include "makeMap.hpp"

const int FLOORSIZE = 8;

void enemyLogic(Enemy & e, Room & r)
{
    cout << "enemyLogic @ (" << e.getPos().x << "," << e.getPos().y << ")\n";
    if(r.flood[e.getPos().x][e.getPos().y] > 1)
    {
        cout << "MOVE @ (" << e.getPos().x << "," << e.getPos().y << ")\n";
        short lowestFlood = r.flood[e.getPos().x][e.getPos().y];
        unsigned short moveDir;
        if(e.getPos().y < MAPSIZE-1 && r.grid[e.getPos().x][e.getPos().y+1] == PATH && r.flood[e.getPos().x][e.getPos().y+1] < lowestFlood) // UP
        {
            lowestFlood = r.flood[e.getPos().x][e.getPos().y+1];
            moveDir = 'U';
        }
        if(e.getPos().y > 0 && r.grid[e.getPos().x][e.getPos().y-1] == PATH && r.flood[e.getPos().x][e.getPos().y-1] < lowestFlood) // DOWN
        {
            lowestFlood = r.flood[e.getPos().x][e.getPos().y-1];
            moveDir = 'D';
        }
        if(e.getPos().x < MAPSIZE-1 && r.grid[e.getPos().x+1][e.getPos().y] == PATH && r.flood[e.getPos().x+1][e.getPos().y] < lowestFlood) // RIGHT
        {
            lowestFlood = r.flood[e.getPos().x+1][e.getPos().y];
            moveDir = 'R';
        }
        if(e.getPos().x > 0 && r.grid[e.getPos().x-1][e.getPos().y] == PATH && r.flood[e.getPos().x-1][e.getPos().y] < lowestFlood) // LEFT
        {
            lowestFlood = r.flood[e.getPos().x-1][e.getPos().y];
            moveDir = 'L';
        }

        switch(moveDir)
        {
            case 'U': // Up North
                cout << "up @ (" << e.getPos().x << "," << e.getPos().y << ")\n";
                r.grid[e.getPos().x][e.getPos().y] = PATH;
                e.setPos({e.getPos().x,e.getPos().y+1});
                r.grid[e.getPos().x][e.getPos().y] = ENEMY;
                break;
            case 'D': // Down South
                cout << "down @ (" << e.getPos().x << "," << e.getPos().y << ")\n";
                r.grid[e.getPos().x][e.getPos().y] = PATH;
                e.setPos({e.getPos().x,e.getPos().y-1});
                r.grid[e.getPos().x][e.getPos().y] = ENEMY;
                break;
            case 'R': //Right East
                cout << "right @ (" << e.getPos().x << "," << e.getPos().y << ")\n";
                r.grid[e.getPos().x][e.getPos().y] = PATH;
                e.setPos({e.getPos().x+1,e.getPos().y});
                r.grid[e.getPos().x][e.getPos().y] = ENEMY;
                break;
            case 'L': // Left West
                cout << "left @ (" << e.getPos().x << "," << e.getPos().y << ")\n";
                r.grid[e.getPos().x][e.getPos().y] = PATH;
                e.setPos({e.getPos().x-1,e.getPos().y});
                r.grid[e.getPos().x][e.getPos().y] = ENEMY;
                break;
            default:
                cout << "default @ (" << e.getPos().x << "," << e.getPos().y << ")\n";
                break;
        }
    }
    else if (r.flood[e.getPos().x][e.getPos().y] == 1) // to prevent glitches when enemies are on flood values "-1"
    {
        cout << "ATTACK @ (" << e.getPos().x << "," << e.getPos().y << ")\n";
        Player::takeDamage(e.getPower());
    }
}

void enemyTurn(Room & r)
{
    for(Enemy & e : r.enemies)
    {
        flood(Player::getPos(),r);
        enemyLogic(e,r);
    }
}


void spawnEnemies(Room & r, int eCount)
{
    // initialize posDeck with all available (path) spawn positions
    vector<Position> posDeck;
    for (int i=0; i<MAPSIZE; i++)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            if (r.grid[i][j] == PATH)
            {
                posDeck.push_back({i,j});
            }
        }
    }

    // randomly spawn enemies on available (path) grid spaces
    for(int i=0; i<eCount; i++)
    {
        Enemy tempEnemy;
        int rint = (int)(std::rand() * posDeck.size() / RAND_MAX);  // random int represents random (path) grid space
        tempEnemy.setPos({posDeck[rint].x,posDeck[rint].y});          // set enemy position to random (path) grid space position
        tempEnemy.setHealth(10.0 * (currentFloor.depth+1));
        tempEnemy.setPower(5.0 * (currentFloor.depth+1));
        tempEnemy.setDefense(1.0 * (currentFloor.depth+1));
        r.grid[posDeck[rint].x][posDeck[rint].y] = ENEMY;           // replace path at random grid space with enemy
        posDeck.erase(posDeck.begin() + rint);                      // remove selected (path) grid space from possible future selection
        r.enemies.push_back(tempEnemy);                             // add enemy to room.enemies vector
    }
}


void flood(Position zero, Room & room)
{
    room.flood.clear();
    room.flood.resize(MAPSIZE,vector<short>(MAPSIZE,-1));
    room.flood[zero.x][zero.y] = 0;
    bool floodComplete = false;
    short floodCount = 0;
    while(!floodComplete)
    {
        floodComplete = true;
        for(int i=0; i < MAPSIZE; i++)
        {
            for(int j=0; j < MAPSIZE; j++)
            {
                if(room.flood[i][j] == floodCount)
                {
                    if(j < MAPSIZE-1 && room.flood[i][j+1] == -1 && (room.grid[i][j+1] == PATH || room.grid[i][j+1] == ENEMY)) // up
                    {
                        room.flood[i][j+1] = floodCount + 1;
                        floodComplete = false;
                    }
                    if(j > 0 && room.flood[i][j-1] == -1 && (room.grid[i][j-1] == PATH || room.grid[i][j-1] == ENEMY)) // down
                    {
                        room.flood[i][j-1] = floodCount + 1;
                        floodComplete = false;
                    }
                    if(i < MAPSIZE-1 && room.flood[i+1][j] == -1 && (room.grid[i+1][j] == PATH || room.grid[i+1][j] == ENEMY)) // right
                    {
                        room.flood[i+1][j] = floodCount + 1;
                        floodComplete = false;
                    }
                    if(i > 0 && room.flood[i-1][j] == -1 && (room.grid[i-1][j] == PATH || room.grid[i-1][j] == ENEMY)) // left
                    {
                        room.flood[i-1][j] = floodCount + 1;
                        floodComplete = false;
                    }
                }
            }
        }
        floodCount++;
    }
}


void testFlood()
{
    cout << "\n\n";
    cout << "FLOOD TESTING\n\n";
    cout << "Flood Testing Hotkeys:\n";
    cout << "f - test print flood\n";
    cout << "\n";
    while(true)
    {
        short key = getKey();
        if(key == '\\') { break; }
        if(key != 'f') { continue; }
        testPrintFlood(Player::getRoom().flood);
    }
    cout << "\n\nEND FLOOD TESTING\n\n";
}


void testPrintFlood(vector<vector<short>> printFlood)
{
    cout << string(2*(MAPSIZE+1),WALL) << endl << WALL;
    for(int i=MAPSIZE-1; i>=0; i--)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            if (printFlood[j][i] == -1){ cout << WALL << WALL; }
            else{ cout << std::setw(2) << printFlood[j][i]; }
        }
        cout << WALL << endl << WALL;
    }
    cout << string(2*(MAPSIZE+1)-1,WALL) << endl;
}

void testMakeRoom(Room & r)
{
	//This is mostly just a test to see if it works
	//cout << "\nMake a Room\n";

    // reset 2D grid and flood vectors to base value
    r.grid.clear();
    r.flood.clear();
    r.grid.resize(MAPSIZE,vector<unsigned char>(MAPSIZE,WALL));
    r.flood.resize(MAPSIZE,vector<short>(MAPSIZE,-1));
    // initialize start and end positions
    for(Door d : r.doors)
    {
        r.grid[d.pos.x][d.pos.y] = PATH;
    }

    // create a vector of all grid positions
    vector<Position> posDeck;
    for (int i=0; i<MAPSIZE; i++)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            posDeck.push_back({i,j});
        }
    }

    // randomly replace walls with paths, one grid space at a time
    // use flood() to determine when end position can be reached from start
    bool keepFlooding = true;
    while (keepFlooding)                           // check if end position can be reached from start position
    {
        keepFlooding = false;
        for(Door d : r.doors)
        {
            if(r.flood[d.pos.x][d.pos.y] == -1)
            {
                keepFlooding = true;
            }
        }
        int rint = (int)(std::rand() * posDeck.size() / RAND_MAX);  // random int represents random grid space
        r.grid[posDeck[rint].x][posDeck[rint].y] = PATH;            // replace wall at random grid space with path
        posDeck.erase(posDeck.begin() + rint);                      // remove selected grid space from possible future selection
        flood({MAPSIZE/2,MAPSIZE/2}, r);                                             // flood from start position
    }

    // Place Entrance and Exit spaces at respective positions
    for(Door d : r.doors)
    {
        r.grid[d.pos.x][d.pos.y] = DOOR;
    }

    // clean up unreachable grid spaces
    for (int i=0; i<MAPSIZE; i++)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            if(r.flood[i][j] == -1)
            {
                r.grid[i][j] = WALL;
            }
        }
    }
    spawnEnemies(r,1);
}

void testMakeFloor(Position entr, Position exit, Floor & f)
{
    f.rooms.clear();
    Room emptyRoom = {}; // feckn whatever dude
    f.rooms.resize(FLOORSIZE,vector<Room>(FLOORSIZE,emptyRoom));

	srand(time(NULL));
	//needs to generate the "maze" and hand each makeroom the entrance and exit positions

	for (int i=0; i <FLOORSIZE-1; i++)
    {
        for(int j=0; j<FLOORSIZE-1; j++)
        {
            if (i > 0)
            {
                Door tempDoor;
                tempDoor.nextRoom = {i-1,j};
                tempDoor.pos = {0,MAPSIZE/2};
                f.rooms[i][j].doors.push_back(tempDoor);
            }
            if (i < FLOORSIZE-1)
            {
                Door tempDoor;
                tempDoor.nextRoom = {i+1,j};
                tempDoor.pos = {MAPSIZE-1,MAPSIZE/2};
                f.rooms[i][j].doors.push_back(tempDoor);
            }
            if (j > 0)
            {
                Door tempDoor;
                tempDoor.nextRoom = {i,j-1};
                tempDoor.pos = {MAPSIZE/2,0};
                f.rooms[i][j].doors.push_back(tempDoor);
            }
            if (j < FLOORSIZE-1)
            {
                Door tempDoor;
                tempDoor.nextRoom = {i,j+1};
                tempDoor.pos = {MAPSIZE/2,MAPSIZE-1};
                f.rooms[i][j].doors.push_back(tempDoor);
            }
            testMakeRoom(f.rooms[i][j]);
        }
    }
}
