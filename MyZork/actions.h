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

Action stringToAction(const string& command);

string& toLowerCase(string& input);


