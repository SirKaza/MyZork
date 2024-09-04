#pragma once
#include "creature.h"
#include <string>

using namespace std;

class Player :
    public Creature
{
    public:
        Player(const string& name, const string& description, Room* location);
        ~Player();

        void Look() const;
        void Go(const string& direction);
        void Take(const vector<string>& args);
        void Inventory() const;
};