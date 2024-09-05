#include "player.h"
#include "room.h"
#include "exit.h"
#include "actions.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player(const string& name, const string& description, Room* location, const bool isContainer)
	: Creature(name, description, location, isContainer) {

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
		bool flag = false;
		for (string arg : args) {
			Entity* item = location->findEntityByNameAndType(arg, TypesEntities::Item); // player only can take items
			if (item != nullptr) { // item found
				flag = true;
				setContains(item); // item in player inventory
				location->removeEntity(item); // pop item from room
				cout << "You took " << item->getName() << ".\n";
			}
		}
		if (flag == false) { // no item found
			cout << "That isn't available.\n";
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
	bool flag = false;
	for (string arg : args) {
		Entity* item = findEntityByNameAndType(arg, TypesEntities::Item); // player only can drop items
		if (item != nullptr) { // item found
			flag = true;
			removeEntity(item); // remove from inventory
			location->setContains(item); // add to room
			cout << "You dropped " << item->getName() << ".\n";
		}
	}
	if (flag == false) {
		cout << "You haven't got that.\n";
	}
}

void Player::Put(const string& item, const string& container) {
	Entity* itemFounded = findEntityByNameAndType(item, TypesEntities::Item); // find item in inventory

	if (itemFounded == nullptr) { // item found
		cout << "You don't have " << item << ".\n";
		return;
	}

	Entity* containerFounded = findEntityByNameAndType(container, TypesEntities::Item); // find container in inventory
	if (containerFounded != nullptr) {
		if (containerFounded->getIsContainer()) {
			containerFounded->setContains(itemFounded);
			removeEntity(itemFounded);
			cout << "You put " << itemFounded->getName() << " in " << containerFounded->getName() << ".\n";
			return;
		}
		cout << "That can't contain things.\n";
		return;
	}

	containerFounded = location->findEntityByNameAndType(container, TypesEntities::Item); // find container in room
	if (containerFounded != nullptr) {
		if (containerFounded->getIsContainer()) {
			containerFounded->setContains(itemFounded);
			removeEntity(itemFounded);
			cout << "You put " << itemFounded->getName() << " in " << containerFounded->getName() << ".\n";
			return;
		}
		cout << "That can't contain things.\n";
		return;
	}

	cout << container << " not available.\n";
}