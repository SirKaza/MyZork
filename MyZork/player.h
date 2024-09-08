#pragma once
#include "creature.h"
#include "lockable.h"
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
        bool Go(const string& direction);
        void Take(const vector<string>& args);
        void Inventory() const;
        void Drop(const vector<string>& args);
        void Put(const vector<string>& args);
        void Examine(const vector<string>& args); // player can not examine an item inside a container
        void Open(const vector<string>& args);
        void Close(const vector<string>& args);
        void Lock(const vector<string>& args);
        void Unlock(const vector<string>& args);

        void examineEntity(Entity* entity) const;
};