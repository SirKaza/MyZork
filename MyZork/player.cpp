#include "player.h"
#include "room.h"
#include "exit.h"
#include "actions.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

Player::Player(const string& name, const string& description, Room* location, const bool isContainer, const string& examineText)
	: Creature(name, description, location, isContainer, examineText) {

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
			cout << "There is nothing to take.\n";
			return;
		}

		for (Entity* item : items) {
			setContains(item); 
			location->removeEntity(item);
			cout << "You took " << item->getName() << ".\n";
		}
		return;
	}

	auto fromPrep = find(args.begin(), args.end(), "from");
	auto ofPrep = find(args.begin(), args.end(), "of");
	if (fromPrep != args.end() || ofPrep != args.end()) { //  Take item From/Of container
		if (args.size() < 3) {
			cout << "What do you want to take from?\n";
			return;
		}

		auto prepPosition = (fromPrep != args.end()) ? fromPrep : ofPrep; // get position of connector

		Entity* containerFound = nullptr;
		for (auto it = prepPosition; it != args.end(); ++it) {
			containerFound = findEntityByNameAndTypes(*it, containerTypes); // find container in inventory
			if (containerFound != nullptr) {
				break;
			}
			containerFound = location->findEntityByNameAndTypes(*it, containerTypes); // find container in inventory
			if (containerFound != nullptr) { 
				break;
			}
		}
		if (containerFound == nullptr) {
			cout << "That can't contain things.\n";
			return;
		}

		Entity* itemFound = nullptr;
		for (auto it = args.begin(); it != prepPosition; ++it) {
			itemFound = containerFound->findEntityByNameAndType(*it, TypesEntities::Item); // find item in container
			if (itemFound != nullptr) { // item found
				break;
			}

		}
		if (itemFound == nullptr) { // no item found in container
			cout << "You can't see any such thing.\n";
			return;
		}

		// have item and container
		containerFound->removeEntity(itemFound);
		setContains(itemFound);
		cout << "You took " << itemFound->getName() << " from " << containerFound->getName() << ".\n";
	}
	else { // take specific items to inventory
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
	if (args[0] == "all" || args[0] == "everything") { // take all items in room
		list<Entity*> items = getContains(); // get inventory

		if (items.empty()) { // player empty of items
			cout << "There is nothing to drop.\n";
			return;
		}

		for (Entity* item : items) {
			removeEntity(item);
			location->setContains(item);
			cout << "You dropped " << item->getName() << ".\n";
		}
	}
	else { // drop specific item
		bool flag = false;
		for (string arg : args) {
			Entity* item = findEntityByName(arg); // player only can drop items
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
}

void Player::Put(const vector<string>& args) {
	vector<string> argsCopy = args;

	Entity* itemFound = nullptr;
	for (auto it = argsCopy.begin(); it != argsCopy.end();) {
		itemFound = findEntityByNameAndType(*it, TypesEntities::Item); // find item in inventory
		it = argsCopy.erase(it);
		if (itemFound != nullptr) { // item found
			break;
		}
		
	}
	if (itemFound == nullptr) { // no item found in args
		cout << "You can't see any such thing.\n";
		return;
	}

	Entity* containerFound = nullptr;
	for (auto it = argsCopy.begin(); it != argsCopy.end(); ++it) {
		containerFound = findEntityByNameAndTypes(*it, containerTypes); // find container in inventory
		if (containerFound != nullptr) { // item found
			if (containerFound->getIsContainer()) {
				containerFound->setContains(itemFound);
				removeEntity(itemFound);
				cout << "You put " << itemFound->getName() << " in " << containerFound->getName() << ".\n";
				return;
			}
			cout << "That can't contain things.\n";
			return;
		}
		containerFound = location->findEntityByNameAndTypes(*it, containerTypes); // find container in room
		if (containerFound != nullptr) { // item found
			if (containerFound->getIsContainer()) {
				containerFound->setContains(itemFound);
				removeEntity(itemFound);
				cout << "You put " << itemFound->getName() << " in " << containerFound->getName() << ".\n";
				return;
			}
			cout << "That can't contain things.\n";
			return;
		}
	}
	cout << "You can't see any such thing.\n";
}

void Player::Examine(const vector<string>& args) {
	// find name, get Type and examine / if container print contains
}