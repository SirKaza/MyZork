#include "creature.h"
#include "room.h"
#include <string>
#include <iostream>

using namespace std;

Creature::Creature(const string& name, const string& description, Room* location)
	: Entity(name, description), location(location) {

	this->type = TypesEntities::CREATURE;
}

Creature::~Creature() {

}

void Creature::display() const {
	cout << name << "\n";
	cout << description << "\n";

	if (location != nullptr) {
		cout << location->getName() << "\n";
	}
	else {
		cout << "Unknown location" << "\n";
	}
}

Room* Creature::getLocation() const {
	return location; // could be null
}