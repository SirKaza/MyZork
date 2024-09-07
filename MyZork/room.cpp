#include "room.h"
#include <string>
#include <iostream>

using namespace std;


Room::Room(const string& name, const string& description, bool isContainer, const string& examineText)
	: Entity(name, description, isContainer, examineText) {

	this->type = TypesEntities::Room;
}


Room::~Room() {

}


void Room::Look() const {
	cout << "Room: " << name << "\n";
	cout << description << "\n";

	for (Entity* entity : contains) {
		entity->Look();
	}
}


const string& Room::getName() const {
	return name;
}


const string& Room::getDescription() const {
	return description;
}