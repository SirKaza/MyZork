#include "player.h"
#include "room.h"
#include "exit.h"
#include "actions.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player(const string& name, const string& description, Room* location) 
	: Creature(name, description, location) {

	this->type = TypesEntities::Player;
}

Player::~Player() {

}

void Player::Look() const {
	cout << name << "\n";
	cout << description << "\n";
}

void Player::Go(const string& direction) {
	for (Entity* entity : location->getContains()) {
		Exit* exit = dynamic_cast<Exit*>(entity); // try downcast to Exit

		if (exit != nullptr) { // Exit
			if (exit->getDirection() == stringToDirection(direction)) {
				location = exit->getDestination(); // Update player location
				cout << "You go " << directionToString(exit->getDirection()) << " and arrive to the " << location->getName() << "\n";
				return;
			}
		}
	}
	cout << "There is no exit in that direction.\n";
}