#pragma once
#include "entity.h"
#include "actions.h"
#include <string>

using namespace std;

class Room;

class Exit :
    public Entity
{
    public:
        Exit(const string& name, const string& description, Direction direction, Room* source, Room* destination, bool isContainer, const string& examineText, bool closed, bool locked);
        ~Exit();

        Direction getDirection() const;
        Room* getSource() const;
        Room* getDestination() const;
        bool isClosed() const;
        bool isLocked() const;

    private:
        Direction direction;
        Room* source;
        Room* destination;

        bool closed;
        bool locked;
};

