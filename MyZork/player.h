#pragma once
#include "creature.h"
#include <string>
#include <set>

using namespace std;

class Player :
    public Creature
{
    public:
        Player(const string& name, const string& description, Room* location, bool isContainer, const string& examineText = "");
        ~Player();

        void Look() const;
        void Go(const string& direction);
        void Take(const vector<string>& args);
        void Inventory() const;
        void Drop(const vector<string>& args);
        void Put(const vector<string>& args);
        void Examine(const vector<string>& args); // player can not examine an item inside a container

        void examineEntity(Entity* entity) const;
};