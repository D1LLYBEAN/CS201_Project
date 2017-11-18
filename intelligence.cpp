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

const char MAPSIZE = 16;
const char PATH = '_';
const char WALL = 219;


void enemyTurn(Enemy e)
{
    if(true){}
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
    Room testRoom;
    Position playerPosition = {0,0};
    shittyPopulateMap(testRoom);
}


void testPrintRoom(vector<vector<unsigned char>> printRoom)
{
    cout << string(2*(MAPSIZE+1),WALL) << endl << WALL;
    for(int i=0; i<MAPSIZE; i++)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            cout << printRoom[i][j] << printRoom[i][j];
        }
        cout << WALL << endl << WALL;
    }
    cout << string(2*(MAPSIZE+1)-1,WALL) << endl;
}


void testPrintFlood(vector<vector<short>> printFlood)
{
    for(int i=0; i<MAPSIZE; i++)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            if (printFlood[i][j] == -1){ cout << WALL << WALL; }
            else{ cout << std::setw(2) << printFlood[i][j]; }
        }
        cout << endl;
    }
}


void shittyPopulateMap(Room & r)
{
    cout << "\nSHITTY POPULATE MAP\n";
    r.grid.resize(MAPSIZE,vector<unsigned char>(MAPSIZE,WALL));
    r.flood.resize(MAPSIZE,vector<short>(MAPSIZE,-1));
    r.grid[0][0] = PATH;
    r.grid[MAPSIZE-1][MAPSIZE-1] = PATH;

    vector<Position> posDeck;
    for (int i=0; i<MAPSIZE; i++)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            posDeck.push_back({i,j});
        }
    }

    std::srand(std::time(0));
    while (r.flood[MAPSIZE-1][MAPSIZE-1] == -1)
    {
        int rint = (int)(std::rand() * posDeck.size() / RAND_MAX);
        r.grid[posDeck[rint].x][posDeck[rint].y] = PATH;
        posDeck.erase(posDeck.begin() + rint);
        flood({0,0}, r);
    }

    cout << "Shitty Generated Room:\n";
    testPrintRoom(r.grid);
    cout << "Flood Vision:\n";
    testPrintFlood(r.flood);

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

    cout << "Final Room:\n";
    testPrintRoom(r.grid);
}
