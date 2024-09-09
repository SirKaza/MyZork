#include "creature.h"
#include "room.h"
#include <string>
#include <iostream>

using namespace std;

Creature::Creature(const string& name, const string& description, Room* location, const string& examineText)
	: Entity(name, description, examineText), location(location){

	this->type = TypesEntities::Creature;
}

Creature::~Creature() {

}

Room* Creature::getLocation() const {
	return location; // could be null
}

void Creature::Look() const {
	if (location != nullptr) {
		cout << name << ": " << description << "\n";
	}
}

bool Creature::Go(const string& direction) {
	return false;
}

void Creature::Take(const vector<string>& args) {

}

void Creature::Inventory() const {

}

void Creature::Drop(const vector<string>& args) {

}

void Creature::Put(const vector<string>& args) {

}

void Creature::Examine(const vector<string>& args) {

}

void Creature::Open(const vector<string>& args) {

}

void Creature::Close(const vector<string>& args) {

}

void Creature::Lock(const vector<string>& args) {

}

void Creature::Unlock(const vector<string>& args) {

}

void Creature::Equip(const vector<string>& args) {

}

void Creature::Unequip(const vector<string>& args) {

}

void Creature::Attack(const vector<string>& args) {

}