#pragma once
#include "entity.h"
#include <string>

using namespace std;

class Room :
    public Entity
{
    public:
        Room(const string& name, const string& description);
        ~Room();

        void Look() const;

        const string& getName() const;
        const string& getDescription() const;
};
        

