#pragma once
#include "entity.h"
#include <string>
#include <vector>

using namespace std;

class Room;

class Creature :
    public Entity
{
    public:
        Creature(const string& name, const string& description, Room* location);
        ~Creature();

        virtual void Look() const;
        virtual void Go(const string& direction);
        virtual void Take(const vector<string>& args);
        virtual void Inventory() const;

        Room* getLocation() const;
        
        
    protected:
        Room* location;
};

