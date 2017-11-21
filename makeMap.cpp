//makeMap.cpp
//
// CS201_Project
// Videogame
//
// Team:
// Grace Bolt
// Liam Eberhart
// Dillon Mills
//
// creates the map, so far just a single room

#include "structs.hpp"
#include <iostream>
#include <ctime>
#include <string>
#include "input.hpp"
using std::string;
using std::cout;
const char MAPSIZE = 16;
const char PATH = '_';
const char WALL = 219;
const char ENTRANCE = '@';
const char EXIT = '@';
const char ENEMY = '&';

void floodFill(Position zero, Room & room)//vector<vector<short>> & floodMap, vector<vector<unsigned char>> roomMap)
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

void showRoom(vector<vector<unsigned char>> printRoom)
{
    cout << string(2*(MAPSIZE+1),WALL) << std::endl << WALL;
    for(int i=MAPSIZE-1; i>=0; i--)
    {
        for(int j=0; j<MAPSIZE; j++)
        {
            cout << printRoom[i][j] << printRoom[i][j];
        }
        cout << WALL << std::endl << WALL;
    }
    cout << string(2*(MAPSIZE+1)-1,WALL) << std::endl;
}

void makeRoom(Position entr, Position exit, Room & r)
{
	//This is mostly just a test to see if it works
	//cout << "\nMake a Room\n";

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
        floodFill(entr, r);                                             // flood from start position
    }

    // Place Entrance and Exit spaces at respective positions
    r.grid[entr.x][entr.y] = ENTRANCE;
    r.grid[exit.x][exit.y] = EXIT;
    
    
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
    cout << "Room:\n";
    showRoom(r.grid);
}

void makeFloor(Position entr, Position exit, Floor & f)
{
	
}

void generateRoom()
{
    while(true)
    {
        Room testRoom;
        Position startPos = {0,0};
        //pick a random number between 0 and 2, less than one is left greater is right.
        Position endPos = {MAPSIZE-1,MAPSIZE-1};
        //pick random number between 0 and 2, less that one is top greater is bottom. 
        makeRoom(startPos,endPos,testRoom);
        short key = getKey();
        if(key == '\\') {break;}
    }
}
