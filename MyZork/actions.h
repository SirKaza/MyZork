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
    Use
};

Action stringToAction(const string& command);


