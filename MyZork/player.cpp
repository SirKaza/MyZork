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
	Direction dir = stringToDirection(direction);

	if (dir == Direction::None) {
		cout << "That is not a valid direction.\n";
		return;
	}

	for (Entity* entity : location->getContains()) {
		Exit* exit = dynamic_cast<Exit*>(entity); // try downcast to Exit

		if (exit != nullptr && exit->getDirection() == dir) {
			location = exit->getDestination(); // Update player location
			cout << "You go " << directionToString(exit->getDirection()) << " and arrive to the " << location->getName() << ".\n";
			return;
		}
	}
	cout << "There is no exit in that direction.\n";
}

void Player::Take(const vector<string>& args) {
	if (args[0] == "all" || args[0] == "everything") { // take all items in room
		list<Entity*> items = location->getContainsByType(TypesEntities::Item);

		if (items.empty()) { // room empty of items
			cout << "There are no items to take.\n";
			return;
		}

		for (Entity* item : items) {
			setContains(item); 
			location->removeEntity(item);
			cout << "You took " << item->getName() << ".\n";
		}
	}
	else { // take specific item
		for (string arg : args) {
			Entity* item = location->findEntityByNameAndType(arg, TypesEntities::Item); // player only can take items
			if (item != nullptr) { // item found
				setContains(item); // item in player inventory
				location->removeEntity(item); // pop item from room
				cout << "You took " << item->getName() << ".\n";
			}
			else {
				cout << "That isn't available.\n";
			}
		}
	}
}

void Player::Inventory() const {
	if (contains.empty()) { // Empty inventory
		cout << "You are empty handed.\n";
	}
	else {
		cout << "You are carrying:\n";
		for (Entity* entity : contains) {
			displayContains(entity, 0);
		}
	}
}

void Player::Drop(const vector<string>& args) {
	for (string arg : args) {
		Entity* item = findEntityByNameAndType(arg, TypesEntities::Item); // player only can drop items
		if (item != nullptr) { // item found
			removeEntity(item); // remove from inventory
			location->setContains(item); // add to room
			cout << "You dropped " << item->getName() << ".\n";
		}
		else {
			cout << "You haven't got that.\n";
		}
	}
}