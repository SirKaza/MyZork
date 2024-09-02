#pragma once
#include "entity.h"
#include <string>

using namespace std;

class Room;

enum class Direction {
    NORTH,
    EAST,
    WEST,
    SOUTH
};

class Exit :
    public Entity
{
    public:
        Exit(const string name, const string description, Direction direction, Room* source, Room* destination);
        ~Exit();

    private:
        Direction direction;
        Room* source;
        Room* destination;
};

