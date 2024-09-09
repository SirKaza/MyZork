#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "actions.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

Player::Player(const string& name, const string& description, Room* location, const string& examineText)
	: Creature(name, description, location, examineText) {

	this->type = TypesEntities::Player;
}

Player::~Player() {

}

void Player::Look() const {
	cout << name << "\n";
	cout << description << "\n";
}

bool Player::Go(const string& direction) {
	Direction dir = stringToDirection(direction);

	if (dir == Direction::None) {
		cout << "That is not a valid direction.\n";
		return false;
	}

	for (Entity* exitEntity : location->getContainsByType(TypesEntities::Exit)) {
		Exit* exit = dynamic_cast<Exit*>(exitEntity); // try downcast to Exit

		if (exit != nullptr && exit->getDirection() == dir) {
			Lockable* lockable = dynamic_cast<Lockable*>(exitEntity); // try downcast to Lockable
			if (lockable != nullptr) {
				if (!lockable->isLocked()) {
					if (!lockable->isClosed()) { // exit open
						location = exit->getDestination(); // Update player location
						cout << "You go " << directionToString(exit->getDirection()) << " and arrive to the " << location->getName() << ".\n";
						return true;
					}
					cout << "You can't go " << directionToString(exit->getDirection()) << " because " << exit->getName() << " is closed.\n";
					return false;
				}
				cout << exit->getName() << " is locked.\n";
				return false;
			}
		}
	}
	cout << "There is no exit in that direction.\n";
	return false;
}

void Player::Take(const vector<string>& args) { // to inventory
	// First case (take all) ----
	if (args[0] == "all" || args[0] == "everything") { // take all items in room
		list<Entity*> itemsEntities = location->getContainsByType(TypesEntities::Item);

		list<Item*> items; 

		bool pickedSomething = false;
		for (Entity* entity : itemsEntities) {
			if (Item* item = dynamic_cast<Item*>(entity)) {
				if (item->isPickable()) {
					setContains(item);
					location->removeEntity(item);
					cout << "You took " << item->getName() << ".\n";
					pickedSomething = true;
				}
			}
		}

		if (!pickedSomething) {
			cout << "There is nothing to take.\n";
		}
		return;
	}

	// Second case (take item from/of container) ----
	auto fromPrep = find(args.begin(), args.end(), "from");
	auto ofPrep = find(args.begin(), args.end(), "of");
	if (fromPrep != args.end() || ofPrep != args.end()) {
		if (args.size() < 3) {
			cout << "What do you want to take from?\n";
			return;
		}

		auto prepPosition = (fromPrep != args.end()) ? fromPrep : ofPrep; // get position of connector

		Entity* containerFound = nullptr;
		for (auto it = prepPosition + 1; it != args.end(); ++it) {
			containerFound = findEntityByNameAndType(*it, TypesEntities::Item); // find container in inventory
			if (containerFound != nullptr) { // container exists and isContainer
				break;
			}
			containerFound = location->findEntityByNameAndType(*it, TypesEntities::Item); // find container in location
			if (containerFound != nullptr) {
				break;
			}
		}
		if (containerFound == nullptr) {
			cout << "That can't contain things.\n";
			return;
		}

		Item* containerItem = dynamic_cast<Item*>(containerFound);
		if (containerItem != nullptr) {
			if (containerItem->isClosed()) {
				cout << containerItem->getName() << " is closed.\n";
				return;
			}
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


		if (containerFound->getType() == TypesEntities::Entity) { 
			containerFound->setExamineText(""); // change examineText
		}
	}

	// Third case (take item/s) ----
	else { 
		bool takeSomething = false;
		for (string arg : args) {
			Entity* entity = location->findEntityByNameAndType(arg, TypesEntities::Item); // player only can take items
			if (entity != nullptr) { // item found
				Item* item = dynamic_cast<Item*>(entity);
				if (item != nullptr) {
					if (item->isPickable()) {
						takeSomething = true;
						setContains(item); // item in player inventory
						location->removeEntity(item); // pop item from room
						cout << "You took " << item->getName() << ".\n";
					}
				}
			}
		}
		if (takeSomething == false) { // no item found
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
	else { // drop specific item/s
		bool dropSomething = false;
		for (string arg : args) {
			Entity* item = findEntityByName(arg); // player only can drop items
			if (item != nullptr) { // item found
				dropSomething = true;
				removeEntity(item); // remove from inventory
				location->setContains(item); // add to room
				cout << "You dropped " << item->getName() << ".\n";
			}
		}
		if (!dropSomething) {
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

	Entity* entity = nullptr;
	for (auto it = argsCopy.begin(); it != argsCopy.end(); ++it) {
		entity = findEntityByNameAndType(*it, TypesEntities::Item); // find container in inventory
		Item* containerFound;
		if (entity != nullptr) { // item found
			containerFound = dynamic_cast<Item*>(entity); // downcast to Item
			if (containerFound != nullptr) {
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
		entity = location->findEntityByNameAndType(*it, TypesEntities::Item); // find container in room
		if (entity != nullptr) { // item found
			containerFound = dynamic_cast<Item*>(entity); // downcast to Item
			if (containerFound != nullptr) {
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
	}
	cout << "You can't see any such thing.\n";
}

void Player::Examine(const vector<string>& args) { 	
	bool foundSomething = false;

	for (const string& arg : args) {
		Entity* entity = findEntityByName(arg); // entity in inventory (item)
		if (entity != nullptr) { //entity found
			entity->Examine();
			foundSomething = true;
			continue;
		}
		entity = location->findEntityByName(arg); // entity in room (item, entity, creature, exit)
		if (entity != nullptr) { //entity found
			entity->Examine();
			foundSomething = true;
			continue;
		}
		if (toLowerCase(location->getName()) == arg) { // entity is room
			location->Examine();
			foundSomething = true;
			continue;
		}
	}
	if (!foundSomething) {
		cout << "You can't see any such thing.\n";
	}
}

void Player::Open(const vector<string>& args) {
	bool foundOpen = false;
	for (const string& arg : args) {
		Entity* entity = location->findEntityByNameAndTypes(arg, lockTypes);
		if (entity != nullptr) {
			foundOpen = true;
			Lockable* open = dynamic_cast<Lockable*>(entity); // downcast to Lockable

			if (open != nullptr) { 
				open->Open(entity->getName());
			}
		}
	}
	if (!foundOpen) {
		cout << "That's not something you can open.\n";
	}
}
void Player::Close(const vector<string>& args) {
	bool foundClose = false;
	for (const string& arg : args) {
		Entity* entity = location->findEntityByNameAndTypes(arg, lockTypes);
		if (entity != nullptr) {
			foundClose = true;
			Lockable* close = dynamic_cast<Lockable*>(entity); // downcast to Exit
			if (close != nullptr) {
				close->Close(entity->getName());
			}
		}
	}
	if (!foundClose) {
		cout << "That's not something you can close.\n";
	}
}

void Player::Lock(const vector<string>& args) {
	if (args.size() < 3) {
		cout << "What do you want to lock with?\n";
		return;
	}

	auto withPrep = find(args.begin(), args.end(), "with");
	if (withPrep != args.end()) {
		
	}
}

void Player::Unlock(const vector<string>& args) {

}