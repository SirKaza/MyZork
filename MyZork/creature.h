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
        Creature(const string& name, const string& description, Room* location, const bool isContainer, const string& examineText = "");
        ~Creature();

        virtual void Look() const;
        virtual void Go(const string& direction);
        virtual void Take(const vector<string>& args);
        virtual void Inventory() const;
        virtual void Drop(const vector<string>& args);
        virtual void Put(const vector<string>& args);
        virtual void Examine(const vector<string>& args);

        Room* getLocation() const;
        
        
    protected:
        Room* location;
};

