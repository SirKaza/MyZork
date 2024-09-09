#pragma once
#include "entity.h"
#include "lockable.h"
#include "actions.h"
#include <string>

using namespace std;

class Room;

class Exit :
    public Entity, public Lockable
{
    public:
        Exit(const string& name, const string& description, Direction direction, Room* source, Room* destination, const string& examineText, bool canClose = false, bool closed = false, bool locked = false);
        ~Exit();

        void Examine() const;

        Direction getDirection() const;
        Room* getSource() const;
        Room* getDestination() const;

    private:
        Direction direction;
        Room* source;
        Room* destination;  
};

