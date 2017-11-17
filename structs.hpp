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


struct Position{
    int x;
    int y;
};

struct Player{
    double health;
    Position pos;
    //...
};

struct Enemy{
    double health;
    Position pos;
    //...
};


#endif // STRUCTS_H
