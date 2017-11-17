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
// Takes input from the user (header).

#include <map>
using std::map;
#include <string>
using std::string;

// Returns any key press by the user,
// ncluding combinations (i.e. Ctrl, Alt, Shift)
short getKey();

//extern map<string,short> keyMap =
//{
////  keyValue    keyName
//    {"ENTER",       0x000D},
//    {"ESC",         0x001B},
//    {"BACKSPACE",   0x0008},
//    {"INSERT",      0xE052},
//    {"DELETE",      0xE053},
//    {"HOME",        0xE047},
//    {"END",         0xE04F},
//    {"PAGEUP",      0xE049},
//    {"PAGEDOWN",    0xE051},
//    {"UPARROW",     0xE048},
//    {"DOWNARROW",   0xE050},
//    {"LEFTARROW",   0xE04B},
//    {"RIGHTARROW",  0xE04D},
//    {"CTRL+A",      0x0001},
//    //...
//    {"CTRL+Z",      0x001A},
//};
