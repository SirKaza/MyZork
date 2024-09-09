#include "creature.h"
#include "room.h"
#include "actions.h"
#include "player.h"
#include "item.h"
#include <string>
#include <iostream>

using namespace std;

Creature::Creature(const string& name, const string& description, Room* location, const string& examineText, Item* weapon, Item* shield)
	: Entity(name, description, examineText), location(location), weapon(weapon), shield(shield) {

	type = TypesEntities::Creature;
	hp = 10;
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
			cout << "What do you want to unequip, weapon or shield?\n";
		}
	}
}

void Creature::RetAttack(Player* player, bool& gameEnded) {
	if (player == nullptr) {
		cout << name << " can't see any such thing to attack.\n";
		return;
	}

	int damage = 0;
	if (weapon != nullptr) { // has weapon equipped
		damage = weapon->getDmg();
		cout << name << " attack " << player->getName() << " with " << weapon->getName() << "!\n";
	}
	else {
		damage = 2; // base damage with hands
		cout << name << " punch " << player->getName() << " with his bare hands!\n";
	}

	if (player->getShield() != nullptr) { // enemy has shield
		damage += player->getShield()->getDmg();
	}

	if (damage < 0) { // dmg cant be negative
		damage = 0;
	}

	// apply damage to creature
	cout << "Dealing " << damage << " damage to " << player->getName() << ".\n";
	player->reduceHp(damage);

	if (player->isDead()) { // player is dead
		cout << player->getName() << " has been slain!\n";
		
		// end game
		cout << "Your adventure ends here. Better luck next time!" << endl;
		gameEnded = true;
	}
	else {
		cout << player->getName() << " has " << player->getHp() << " health remaining.\n";
	}
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

int Creature::getHp() const {
	return hp;
}

void Creature::reduceHp(int damage) {
	hp -= damage;
	if (hp < 0) {
		hp = 0; // cant be negative hp
	}
}

bool Creature::isDead() const {
	if (hp == 0) {
		return true;
	}
	else {
		return false;
	}
}