#pragma once
#include "entity.h"
#include "lockable.h"
#include <string>

using namespace std;

class Item :
    public Entity, public Lockable
{
    public:
        Item(const string& name, const string& description, bool pickable = false, bool isContainer = false, const string& examineText = "", TypesItems itemType = TypesItems::Normal, bool canClose = false, bool closed = false, bool locked = false, const string& key = "");
        ~Item();

        void Examine() const;

        bool isPickable() const;
        const bool getIsContainer() const;
        TypesItems getItemType() const;
        int getDmg() const;
        void setDmg(int newDmg);
    private:
        bool pickable; // item can be picked
        bool isContainer; // flag for items that player can put things inside it
        TypesItems itemType;
        int dmg; // damage of weapon or shield (shield will protect)
};

