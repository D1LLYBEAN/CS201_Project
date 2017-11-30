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

void enemyLogic(Enemy & e, Room & r)
{
    if(r.flood[e.pos.x][e.pos.y] > 0)
    {
        short lowestFlood = r.flood[e.pos.x][e.pos.y];
        char moveDir;
        Position movePos;
        if(e.pos.y < MAPSIZE-1 && r.flood[e.pos.x][e.pos.y+1] > -1 && r.flood[e.pos.x][e.pos.y+1] < lowestFlood) // UP
        {
            lowestFlood = r.flood[e.pos.x][e.pos.y+1];
            moveDir = 'U';
            movePos = {e.pos.x,e.pos.y+1};
        }
        if(e.pos.y > 0 && r.flood[e.pos.x][e.pos.y-1] > -1 && r.flood[e.pos.x][e.pos.y-1] < lowestFlood) // DOWN
        {
            lowestFlood = r.flood[e.pos.x][e.pos.y-1];
            moveDir = 'D';
            movePos = {e.pos.x,e.pos.y-1};
        }
        if(e.pos.x < MAPSIZE-1 && r.flood[e.pos.x+1][e.pos.y] > -1 && r.flood[e.pos.x+1][e.pos.y] < lowestFlood) // RIGHT
        {
            lowestFlood = r.flood[e.pos.x+1][e.pos.y];
            moveDir = 'R';
            movePos = {e.pos.x+1,e.pos.y};
        }
        if(e.pos.x > 0 && r.flood[e.pos.x-1][e.pos.y] > -1 && r.flood[e.pos.x-1][e.pos.y] < lowestFlood) // LEFT
        {
            lowestFlood = r.flood[e.pos.x-1][e.pos.y];
            moveDir = 'L';
            movePos = {e.pos.x-1,e.pos.y};
        }
        if(moveDir >= 0)
        {
            //moveChar(e,r);                // HELD UP BY INCOMPLETE moveChar() FUNCTION!
            cout << r.flood[e.pos.x][e.pos.y] << " (" << e.pos.x << "," << e.pos.y << ") " << moveDir << " " << r.flood[movePos.x][movePos.y] << " (" << movePos.x << "," << movePos.y << ")\n";
        }
    }
}

void enemyTurn(Room & r)
{
    for(Enemy e : r.enemies)
        enemyLogic(e,r);
}


void spawnEnemies(Room & r)
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
    for(int i=0; i<5; i++)
    {
        Enemy tempEnemy;
        tempEnemy.health = 10.0;                                    // initialize enemy health
        int rint = (int)(std::rand() * posDeck.size() / RAND_MAX);  // random int represents random (path) grid space
        tempEnemy.pos = {posDeck[rint].x,posDeck[rint].y};          // set enemy position to random (path) grid space position
        r.grid[posDeck[rint].x][posDeck[rint].y] = ENEMY;           // replace path at random grid space with enemy
        posDeck.erase(posDeck.begin() + rint);                      // remove selected (path) grid space from possible future selection
        r.enemies.push_back(tempEnemy);                             // add enemy to room.enemies vector
    }
}


void flood(Position zero, Room & room)//vector<vector<short>> & floodMap, vector<vector<unsigned char>> roomMap)
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
                    if(j < MAPSIZE-1 && room.flood[i][j+1] == -1 && room.grid[i][j+1] == PATH) // up
                    {
                        room.flood[i][j+1] = floodCount + 1;
                        floodComplete = false;
                    }
                    if(j > 0 && room.flood[i][j-1] == -1 && room.grid[i][j-1] == PATH) // down
                    {
                        room.flood[i][j-1] = floodCount + 1;
                        floodComplete = false;
                    }
                    if(i < MAPSIZE-1 && room.flood[i+1][j] == -1 && room.grid[i+1][j] == PATH) // right
                    {
                        room.flood[i+1][j] = floodCount + 1;
                        floodComplete = false;
                    }
                    if(i > 0 && room.flood[i-1][j] == -1 && room.grid[i-1][j] == PATH) // left
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
    cout << "f - Shitty Generate\n";
    cout << "\n";
    while(true)
    {
        short key = getKey();
        if(key == '\\') { break; }
        if(key != 'f') { continue; }
        Room testRoom;
        Position startPos = {0,0};
        Position endPos = {MAPSIZE-1,MAPSIZE-1};
        shittyPopulateMap(startPos,endPos,testRoom);
        enemyTurn(testRoom);
    }
    cout << "\n\nFLOOD TESTING ENDED\n\n";
}


void testPrintRoom(vector<vector<unsigned char>> printRoom)
{
    cout << string(MAPSIZE+2,WALL) << endl << WALL;
    for(int i=MAPSIZE-1; i>=0; i--)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            cout << printRoom[j][i];
        }
        cout << WALL << endl << WALL;
    }
    cout << string(MAPSIZE+1,WALL) << endl;
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


void shittyPopulateMap(Position entr, Position exit, Room & r)
{
    cout << "\nSHITTY POPULATE MAP\n";

    // reset 2D grid and flood vectors to base value
    r.grid.clear();
    r.flood.clear();
    r.grid.resize(MAPSIZE,vector<unsigned char>(MAPSIZE,WALL));
    r.flood.resize(MAPSIZE,vector<short>(MAPSIZE,-1));

    // initialize start and end positions
    r.grid[entr.x][entr.y] = PATH;
    r.grid[exit.x][exit.y] = PATH;

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
    std::srand(std::time(0));
    while (r.flood[exit.x][exit.y] == -1)                           // check if end position can be reached from start position
    {
        int rint = (int)(std::rand() * posDeck.size() / RAND_MAX);  // random int represents random grid space
        r.grid[posDeck[rint].x][posDeck[rint].y] = PATH;            // replace wall at random grid space with path
        posDeck.erase(posDeck.begin() + rint);                      // remove selected grid space from possible future selection
        flood(entr, r);                                             // flood from start position
    }

    // Place Entrance and Exit spaces at respective positions
    r.grid[entr.x][entr.y] = ENTRANCE;
    r.grid[exit.x][exit.y] = EXIT;

    // print shitty room, and print what can be seen by flood()
//    cout << "Shitty Room:\n";
//    testPrintRoom(r.grid);
//    cout << "Flood Vision:\n";
//    testPrintFlood(r.flood);

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

    spawnEnemies(r);

    // print room with enemies
//    cout << "Clean Room (Populated):\n";
//    testPrintRoom(r.grid);
}
