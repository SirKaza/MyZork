#pragma once
#include "entity.h"
#include <string>

using namespace std;

class Item :
    public Entity
{
    public:
        Item(const string& name, const string& description, const bool isContainer, const string& examineText = "");
        ~Item();
};

