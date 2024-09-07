#include "creature.h"
#include "room.h"
#include <string>
#include <iostream>

using namespace std;

Creature::Creature(const string& name, const string& description, Room* location, bool isContainer, const string& examineText)
	: Entity(name, description, isContainer, examineText), location(location) {

	this->type = TypesEntities::Creature;
}

Creature::~Creature() {

}

void Creature::Look() const {
	cout << name << "\n";
	cout << description << "\n";

	if (location != nullptr) {
		cout << location->getName() << "\n";
	}
	else {
		cout << "Unknown location\n";
	}
}

void Creature::Go(const string& direction) {

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


Room* Creature::getLocation() const {
	return location; // could be null
}