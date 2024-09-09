#pragma once
#include <string>
#include <set>

using namespace std;

enum class TypesEntities {
    Entity,
    Creature,
    Exit,
    Room,
    Item,
    Player
};

enum class Action {
    Look,
    Go,
    Take,
    Drop,
    Quit,
    Inventory,
    Examine,
    Put,
    Open,
    Close,
    Lock,
    Unlock,
    Equip,
    Unequip,
    Attack,
    Repeat,
    Extra,
    Help
};

enum class Direction {
    North,
    East,
    West,
    South,
    Up,
    Down,
    None
};

const set<TypesEntities> lockTypes = { TypesEntities::Item, TypesEntities::Entity, TypesEntities::Exit };

Action stringToAction(const string& command);

string toLowerCase(const string& input);
string& toLowerCaseModify(string& input);

Direction stringToDirection(const string& direction);
string directionToString(Direction direction);

void printHelp();


