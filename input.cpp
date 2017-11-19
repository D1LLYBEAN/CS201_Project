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

#ifdef _WIN32

#include <conio.h>
#include "input.hpp"

// Returns any key press by the user,
// including combinations (i.e. Ctrl, Alt, Shift)
short getKey()
{
    short key = getch();
    if (key == 0x00)
    {
        key = 0x01 + getch(); // distinguish from 0x00, and retrieve second byte of extended code
    }
    else if (key == 0xE0)
    {
        key = 0xE0 + getch(); // retrieve second byte of extended code
    }
    return key;
}

#endif // _WIN32
#ifdef __MACH__

#include <iostream>
using std::cin;
#include <string>
using std::string;
#include "input.hpp"

// Returns any key press by the user,
// including combinations (i.e. Ctrl, Alt, Shift)
short getKey()
{
    string line;
    getline(cin,line);
    short key = line.back();

    return key;
}

// BELOW IS SOMETHING I FOUND ONLINE THAT MIGHT WORK LIKE getch() FOR MAC

//#include <termios.h>
//#include <unistd.h>
//#include <stdio.h>
//
//
///* reads from keypress, doesn't echo */
//int mygetch(void)
//{
//    struct termios oldattr, newattr;
//    int ch;
//    tcgetattr( STDIN_FILENO, &oldattr );
//    newattr = oldattr;
//    newattr.c_lflag &= ~( ICANON | ECHO );
//    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
//    ch = getchar();
//    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
//    return ch;
//}

#endif // __MACH__
#ifdef __linux__

// MAY NOT NEED TO BE DIFFERENT THAN __MACH__
// MAYBE GUARD BOTH UNDER __unix__

//...

#endif // __linux__
