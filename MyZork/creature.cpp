#include "creature.h"
#include "room.h"
#include "actions.h"
#include "item.h"
#include <string>
#include <iostream>

using namespace std;

Creature::Creature(const string& name, const string& description, Room* location, const string& examineText, Item* weapon, Item* shield)
	: Entity(name, description, examineText), location(location), weapon(weapon), shield(shield) {

	this->type = TypesEntities::Creature;
}

Creature::~Creature() {

}

void Creature::Look() const {
	if (location != nullptr) {
		cout << name << ": " << description << "\n";
		Inventory();
	}
}

bool Creature::Go(const string& direction) {
	return false;
}

void Creature::Take(const vector<string>& args) {

}

void Creature::Inventory() const {
	if (weapon != nullptr || shield != nullptr) {
		cout << "Equipment:\n";
		if (weapon != nullptr) {
			cout << " Weapon: " << weapon->getName() << ".\n";
		}
		if (shield != nullptr) {
			cout << " Shield: " << shield->getName() << ".\n";
		}
	}
}

void Creature::Drop(const vector<string>& args) {

}

void Creature::Put(const vector<string>& args) {

}

void Creature::Examine(const vector<string>& args) {
	if (!examineText.empty()) {
		cout << examineText << "\n";
	}
	else {
		cout << "I see nothing special about " << name << ".\n";
	}

	if (weapon != nullptr || shield != nullptr) {
		cout << "Has equipped:\n";
		if (weapon != nullptr) {
			cout << " Weapon: " << weapon->getName() << ".\n";
		}
		if (shield != nullptr) {
			cout << " Shield: " << shield->getName() << ".\n";
		}
	}
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
	Item* itemFound = nullptr;

	for (const string& arg : args) {
		itemFound = dynamic_cast<Item*>(findEntityByNameAndType(arg, TypesEntities::Item)); // from inventory
		if (itemFound != nullptr) {
			break;
		}
	}

	if (itemFound == nullptr) {
		cout << "You can't see any such thing to equip.\n";
		return;
	}

	TypesItems itemType = itemFound->getItemType();

	switch (itemType)
	{
	case TypesItems::Weapon:
		if (weapon == nullptr) { // no weapon equipped
			weapon = itemFound;
			removeEntity(itemFound); // delete from inventory
			cout << "You have equipped " << itemFound->getName() << " as a weapon.\n";
		}
		else {
			cout << "You already have " << weapon->getName() << " equipped. Unequip it first.\n";
		}
		break;

	case TypesItems::Shield:
		if (shield == nullptr) { // no shield equipped
			shield = itemFound;
			removeEntity(itemFound); // delete from inventory
			cout << "You have equipped " << itemFound->getName() << " as a shield.\n";
		}
		else {
			cout << "You already have " << shield->getName() << " equipped. Unequip it first.\n";
		}
		break;

	default:
		cout << "You can't equip " << itemFound->getName() << ".\n";
		break;
	}
}

void Creature::Unequip(const vector<string>& args) {
	for (const string& itemType : args) {
		if (itemType == "weapon") {
			if (weapon != nullptr) { // equipped
				cout << "You have unequipped " << weapon->getName() << ".\n";
				setContains(weapon);
				weapon = nullptr;
			}
			else {
				cout << "You don't have a weapon equipped.\n";
			}
		}
		else if (itemType == "shield") {
			if (shield != nullptr) {
				cout << "You have unequipped " << shield->getName() << ".\n";
				setContains(shield);
				shield = nullptr;
			}
			else {
				cout << "You don't have a shield equipped.\n";
			}
		}
		else {
			cout << "You don't have " << itemType << ".\n";
		}
	}
}

void Creature::Attack(const vector<string>& args) {

}

Room* Creature::getLocation() const {
	return location; // could be null
}

Item* Creature::getWeapon() const {
	return weapon;
}

Item* Creature::getShield() const {
	return shield;
}