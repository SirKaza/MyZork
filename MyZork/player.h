#pragma once
#include "creature.h"
#include <string>
#include <set>

using namespace std;

class Player :
    public Creature
{
    public:
        Player(const string& name, const string& description, Room* location, const bool isContainer, const string& examineText = "");
        ~Player();

        void Look() const;
        void Go(const string& direction);
        void Take(const vector<string>& args);
        void Inventory() const;
        void Drop(const vector<string>& args);
        void Put(const vector<string>& args);
        void Examine(const vector<string>& args);

        void examineEntity(Entity* entity) const;
};