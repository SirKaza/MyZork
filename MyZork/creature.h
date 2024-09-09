#pragma once
#include "entity.h"
#include <string>
#include <vector>

using namespace std;

class Room;
class Item;

class Creature :
    public Entity
{
    public:
        Creature(const string& name, const string& description, Room* location, const string& examineText = "", Item* weapon = nullptr, Item* shield = nullptr);
        ~Creature();

        virtual void Look() const;
        virtual bool Go(const string& direction);
        virtual void Take(const vector<string>& args);
        virtual void Inventory() const;
        virtual void Drop(const vector<string>& args);
        virtual void Put(const vector<string>& args);
        virtual void Examine(const vector<string>& args);
        virtual void Open(const vector<string>& args);
        virtual void Close(const vector<string>& args);
        virtual void Lock(const vector<string>& args);
        virtual void Unlock(const vector<string>& args);
        virtual void Equip(const vector<string>& args);
        virtual void Unequip(const vector<string>& args);
        virtual void Attack(const vector<string>& args);

        Room* getLocation() const;
        Item* getWeapon() const;
        Item* getShield() const;
        
    protected:
        Room* location;
        Item* weapon;
        Item* shield;
};

