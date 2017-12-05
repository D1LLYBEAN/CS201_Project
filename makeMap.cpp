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
#include "input.hpp"
#include "intelligence.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <time.h>
using std::string;
using std::cout;
const int FLOORSIZE = 4;


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

void printFloor(Floor f)
{
	//does not include left side wall...
	//cout << string((FLOORSIZE*MAPSIZE+FLOORSIZE),(char)WALL) << std::endl;
	for(int fY = FLOORSIZE-1; fY >= 0; fY--) //increment floor y
	{
		for(int rY = MAPSIZE-1; rY >= 0; rY--) //increment room y
		{
			for(int fX = 0; fX < FLOORSIZE; fX++) //increment floor x
			{
				for(int rX = 0; rX < MAPSIZE; rX++) //increment room x
				{
					cout << f.rooms[fX][fY].grid[rX][rY];
				}
				//cout << (char)WALL;
				//cout << "TEST ME:\n";
			}
			cout << std:: endl;
		}
		//cout << string((FLOORSIZE*MAPSIZE+FLOORSIZE),(char)WALL) << std::endl;
	}
	cout << std:: endl;
}


void makeRoom(Room & r)
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

void makeFloor(Position entr, Position exit, Floor & f)
{
    f.rooms.clear();
    Room emptyRoom = {}; // feckn whatever dude
    f.rooms.resize(FLOORSIZE,vector<Room>(FLOORSIZE,emptyRoom));

	srand(time(NULL));
	//needs to generate the "maze" and hand each makeroom the entrance and exit positions

	for (int i=0; i <FLOORSIZE; i++)
    {
        for(int j=0; j<FLOORSIZE; j++)
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
            makeRoom(f.rooms[i][j]);
        }
    }
}

//void makeRoom(Position entr, Position exit, Room & r)
//{
//	//This is mostly just a test to see if it works
//	//cout << "\nMake a Room\n";
//
//    // reset 2D grid and flood vectors to base value
//    r.grid.clear();
//    r.flood.clear();
//    r.grid.resize(MAPSIZE,vector<unsigned char>(MAPSIZE,WALL));
//    r.flood.resize(MAPSIZE,vector<short>(MAPSIZE,-1));
//    // initialize start and end positions
//    r.grid[entr.x][entr.y] = PATH;
//    r.grid[exit.x][exit.y] = PATH;
//
//    // create a vector of all grid positions
//    vector<Position> posDeck;
//    for (int i=0; i<MAPSIZE; i++)
//    {
//        for(int j=0; j<MAPSIZE; j++)
//        {
//            posDeck.push_back({i,j});
//        }
//    }
//
//    // randomly replace walls with paths, one grid space at a time
//    // use flood() to determine when end position can be reached from start
//
//    while (r.flood[exit.x][exit.y] == -1)                           // check if end position can be reached from start position
//    {
//        int rint = (int)(std::rand() * posDeck.size() / RAND_MAX);  // random int represents random grid space
//        r.grid[posDeck[rint].x][posDeck[rint].y] = PATH;            // replace wall at random grid space with path
//        posDeck.erase(posDeck.begin() + rint);                      // remove selected grid space from possible future selection
//        floodFill(entr, r);                                             // flood from start position
//    }
//
//    // Place Entrance and Exit spaces at respective positions
//    r.grid[entr.x][entr.y] = ENTRANCE;
//    r.grid[exit.x][exit.y] = EXIT;
//
//
//    // clean up unreachable grid spaces
//    for (int i=0; i<MAPSIZE; i++)
//    {
//        for(int j=0; j<MAPSIZE; j++)
//        {
//            if(r.flood[i][j] == -1)
//            {
//                r.grid[i][j] = WALL;
//            }
//        }
//    }
//    spawnEnemies(r,1);
//    //cout << "Room:\n";
//    //showRoom(r.grid);
//}

//void makeFloor(Position entr, Position exit, Floor & f)
//{
//	srand(time(NULL));
//	vector< vector<Room> > rooms = f.rooms;
//	//needs to generate the "maze" and hand each makeroom the entrance and exit positions
//
//	//Position testEnter = {0,0};
//	//Position testExit = {MAPSIZE-1,MAPSIZE-1};
//	for(auto i = 0; i < FLOORSIZE; ++i)
//	{
//		vector<Room> rowRoom;
//		for(auto j = 0; j < FLOORSIZE; ++j)
//		{
//			Room testRoom;
//			Position roomSpot = {i, j};
//			testRoom.pos = roomSpot;
//			if( roomSpot.y == entr.y && roomSpot.x == entr.x ) // floor entrance room
//			{
//				makeRoom({MAPSIZE/2,MAPSIZE/2},{MAPSIZE-1,MAPSIZE/2},testRoom);
//				testRoom.exits.push_back({MAPSIZE/2,MAPSIZE/2});
//				testRoom.exits.push_back({MAPSIZE-1,MAPSIZE/2});
//			}
//			else if( roomSpot.y == exit.y && roomSpot.x == exit.x && (FLOORSIZE%2 == 1)) // floor exit room odd
//			{
//				makeRoom({0,MAPSIZE/2},{MAPSIZE/2,MAPSIZE/2},testRoom);
//				testRoom.exits.push_back({0,MAPSIZE/2});
//				testRoom.exits.push_back({MAPSIZE/2,MAPSIZE/2});
//			}
//			else if( roomSpot.y == FLOORSIZE-1 && roomSpot.x == 0 && (FLOORSIZE%2 == 0)) // floor exit room even
//			{
//				makeRoom({MAPSIZE-1,MAPSIZE/2},{MAPSIZE/2,MAPSIZE/2},testRoom);
//				testRoom.exits.push_back({MAPSIZE-1,MAPSIZE/2});
//				testRoom.exits.push_back({MAPSIZE/2,MAPSIZE/2});
//			}
//			else if((roomSpot.x == FLOORSIZE-1) && (roomSpot.y%2 == 1)) // entrance left middle and exit top middle
//			{
//				makeRoom({0, MAPSIZE/2}, {MAPSIZE/2, 0}, testRoom);
//				testRoom.exits.push_back({0, MAPSIZE/2});
//				testRoom.exits.push_back({MAPSIZE/2, 0});
//			}
//			else if((roomSpot.x == FLOORSIZE-1) && (roomSpot.y%2 == 0) ) // entrance left middle and exit bottom middle
//			{
//				makeRoom({0, MAPSIZE/2}, {MAPSIZE/2, MAPSIZE-1}, testRoom);
//				testRoom.exits.push_back({0, MAPSIZE/2});
//				testRoom.exits.push_back({MAPSIZE/2, MAPSIZE-1});
//			}
//			else if((roomSpot.x == 0) && (roomSpot.y%2 == 0)) // entrance right middle and exit bottom middle
//			{
//				makeRoom({MAPSIZE-1, MAPSIZE/2}, {MAPSIZE/2, 0}, testRoom);
//				testRoom.exits.push_back({MAPSIZE-1, MAPSIZE/2});
//				testRoom.exits.push_back({MAPSIZE/2, 0});
//			}
//			else if((roomSpot.x == 0) && (roomSpot.y%2 == 1) ) // entrance right middle and exit top middle
//			{
//				makeRoom({MAPSIZE-1, MAPSIZE/2}, {MAPSIZE/2, MAPSIZE-1}, testRoom);
//				testRoom.exits.push_back({MAPSIZE-1, MAPSIZE/2});
//				testRoom.exits.push_back({MAPSIZE/2, MAPSIZE-1});
//			}
//			else
//			{
//				makeRoom({0,MAPSIZE/2},{MAPSIZE-1,MAPSIZE/2},testRoom); // Middle rooms.
//				testRoom.exits.push_back({0,MAPSIZE/2});
//				testRoom.exits.push_back({MAPSIZE-1,MAPSIZE/2});
//			}
//			rowRoom.push_back(testRoom);
//		}
//		rooms.push_back(rowRoom);
//	}
//	f.rooms = rooms;
//}




//void nextRoom(int dir)
//{
//	Room currentRoom = Player::getRoom();
//	//Position playerPos = Player::getPos();
//	if(dir==0)// TOP
//	{
//		currentRoom.pos.y++;
//	}
//	if(dir==1)// RIGHT
//	{
//		currentRoom.pos.x++;
//	}
//	if(dir==2)// BOTTOM
//	{
//		currentRoom.pos.y--;
//	}
//	if(dir==3)// LEFT
//	{
//		currentRoom.pos.x--;
//	}
//
//	Player::setRoom(currentFloor.rooms[currentRoom.pos.x][currentRoom.pos.y]);
//	Player::setPos(currentRoom.exits[0]);
//}

//void generateRoom()
//{
//	std::srand(std::time(0));
//    while(true)
//    {
//    	short key = getKey();
//    	if(key == '\\') {break;}
//    	if(key == 'g')
//		{
//	        Floor testFloor;
//	        Position startPos = {0,0};
//	        //pick a random number between 0 and 2, less than one is left greater is right.
//	        Position endPos = {FLOORSIZE-1,FLOORSIZE-1};
//	        //pick random number between 0 and 2, less that one is top greater is bottom.
//	        makeFloor(startPos,endPos,testFloor);
//	        printFloor(testFloor);
//		}
//    }
//    cout << "Exited generate.";
//}
