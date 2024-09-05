#pragma once
#include <string>

using namespace std;

enum class Action {
    Look,
    Go,
    Take,
    Drop,
    Quit,
    Inventory,
    Examine,
    Put,
    Repeat,
    Use
};

enum class Direction {
    North,
    East,
    West,
    South,
    Up,
    Down,
    None
};

Action stringToAction(const string& command);

string& toLowerCase(string& input);

Direction stringToDirection(const string& direction);
string directionToString(Direction direction);


