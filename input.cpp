// input.cpp
//
// CS201_Project
// Videogame
//
// Team:
// Grace Bolt
// Liam Eberhart
// Dillon Mills
//
// Takes input from the user.

// Standard Libraries
//#include <conio.h>      // for getch()
#include <iostream>
using std::cin;
#include <string>
using std::string;
//using std::back;
// Custom Libraries
#include "input.hpp"


// Returns any key press by the user,
// including combinations (i.e. Ctrl, Alt, Shift)
short getKey()
{
//    short key = getch();
//    if (key == 0x00)
//    {
//        key = 0x01 + getch(); // distinguish from 0x00, and retrieve second byte of extended code
//    }
//    else if (key == 0xE0)
//    {
//        key = 0xE0 + getch(); // retrieve second byte of extended code
//    }

    string line;
    getline(cin,line);
    short key = line.back();

    return key;
}
