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
    Open,
    Close,
    Repeat,
    Extra,
    Help
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

string toLowerCase(const string& input);
string& toLowerCaseModify(string& input);

Direction stringToDirection(const string& direction);
string directionToString(Direction direction);

void printHelp();


