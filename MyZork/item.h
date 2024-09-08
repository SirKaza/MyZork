#pragma once
#include "entity.h"
#include "lockable.h"
#include <string>

using namespace std;

class Item :
    public Entity, public Lockable
{
    public:
        Item(const string& name, const string& description, bool isContainer, const string& examineText = "", bool canClose = false, bool closed = false, bool locked = false);
        ~Item();
};

