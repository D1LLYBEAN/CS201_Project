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
