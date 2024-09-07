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
        Exit(const string& name, const string& description, Direction direction, Room* source, Room* destination, bool isContainer, const string& examineText, const bool canClose = false, bool closed = false, bool locked = false);
        ~Exit();

        void Examine() const;

        Direction getDirection() const;
        Room* getSource() const;
        Room* getDestination() const;

        bool isClosed() const;
        bool isLocked() const;
        const bool getCanClose() const;
        void inverseClosed();
        void inverseLocked();

    private:
        Direction direction;
        Room* source;
        Room* destination;

        bool closed;
        bool locked;
        const bool canClose; // exit can be closed or opened
};

