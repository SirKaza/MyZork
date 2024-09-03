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

        void display();
};