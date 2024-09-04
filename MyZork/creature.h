#pragma once
#include "entity.h"
#include <string>

using namespace std;

class Room;

class Creature :
    public Entity
{
    public:
        Creature(const string& name, const string& description, Room* location);
        ~Creature();

        virtual void Look() const;
        virtual void Go(const string& point);

        Room* getLocation() const;
        
        
    protected:
        Room* location;
};

