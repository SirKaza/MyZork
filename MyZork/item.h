#pragma once
#include "entity.h"
#include "lockable.h"
#include <string>

using namespace std;

class Item :
    public Entity, public Lockable
{
    public:
        Item(const string& name, const string& description, bool pickable = false, bool isContainer = false, const string& examineText = "", bool canClose = false, bool closed = false, bool locked = false);
        ~Item();

        void Examine() const;

        bool isPickable() const;
        const bool getIsContainer() const;
    private:
        bool pickable; // item can be picked
        bool isContainer; // flag for items that player can put things inside it
};

