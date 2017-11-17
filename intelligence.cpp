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
// Custom Libraries
#include "intelligence.hpp"
#include "structs.hpp"

const char MAPSIZE = 16;
const char PATH = '_';
const char WALL = 219;

void flood(Position pPos, vector<vector<short>> & floodMap, vector<vector<char>> roomMap)
{
    floodMap.resize(MAPSIZE,vector<short>(MAPSIZE,-1));
    floodMap[pPos.x][pPos.y] = 0;
    bool floodComplete = false;
    short floodCount = 0;
    while(!floodComplete && floodCount < MAPSIZE*MAPSIZE)
    {
        floodComplete = true;
        for(int i=0; i < MAPSIZE-1; i++)
        {
            for(int j=0; j < MAPSIZE-1; j++)
            {
                if(floodMap[i][j] == floodCount)
                {
                    if(j < MAPSIZE && floodMap[i][j+1] == -1 && roomMap[i][j+1] == PATH) // up
                    {
                        floodMap[i][j+1] = floodCount + 1;
                        floodComplete = false;
                    }
                    if(j > 0 && floodMap[i][j-1] == -1 && roomMap[i][j-1] == PATH) // down
                    {
                        floodMap[i][j-1] = floodCount + 1;
                        floodComplete = false;
                    }
                    if(i < MAPSIZE && floodMap[i+1][j] == -1 && roomMap[i+1][j] == PATH) // right
                    {
                        floodMap[i+1][j] = floodCount + 1;
                        floodComplete = false;
                    }
                    if(i > 0 && floodMap[i-1][j] == -1 && roomMap[i-1][j] == PATH) // left
                    {
                        floodMap[i-1][j] = floodCount + 1;
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
    vector<vector<char>> testRoomMap;
    vector<vector<short>> testFloodMap;
    Position playerPosition = {0,0};
    shittyPopulateMap(testRoomMap);
    flood(playerPosition, testFloodMap, testRoomMap);
    cout << "\nActual Room:";
    testPrintRoom(testRoomMap);
    cout << "Flood-vision:";
    testPrintFlood(testFloodMap);
    cout << endl;
}


void testPrintRoom(vector<vector<char>> printRoom)
{
    cout << endl;
    for(int i=0; i<MAPSIZE; i++)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            cout << std::setw(2) << printRoom[i][j] << printRoom[i][j];
        }
        cout << endl;
    }
}


void testPrintFlood(vector<vector<short>> printFlood)
{
    cout << endl;
    for(int i=0; i<MAPSIZE; i++)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            if (printFlood[i][j] == -1){ cout << WALL << WALL << " "; }
            else{ cout << std::setw(2) << printFlood[i][j] << " "; }
        }
        cout << endl;
    }
}


void shittyPopulateMap(vector<vector<char>> & popMap)
{
    std::srand(std::time(0));
    vector<vector<short>> fMap;
    popMap.resize(MAPSIZE,vector<char>(MAPSIZE,WALL));
    popMap[0][0] = PATH;
    popMap[10][10] = PATH;
    short floodCount = 0;
    while(floodCount < MAPSIZE*MAPSIZE)
    {
        int intX = (int)(std::rand()*MAPSIZE/RAND_MAX);
        int intY = (int)(std::rand()*MAPSIZE/RAND_MAX);

        popMap[intX][intY] = PATH;
        flood({0,0}, fMap, popMap);
        if (fMap[10][10] != -1) {break;}
        floodCount++;
    }
}
