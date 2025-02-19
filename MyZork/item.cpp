#include "item.h"
#include <iostream>

using namespace std;

Item::Item(const string& name, const string& description, bool pickable, bool isContainer, const string& examineText, TypesItems itemType, bool canClose, bool closed, bool locked, const string& key)
	: Entity(name, description, examineText), Lockable(canClose, closed, locked, key), pickable(pickable), isContainer(isContainer), itemType(itemType) {
	
	this->type = TypesEntities::Item;
	this->dmg = 0;
}

Item::~Item() {

}

void Item::Examine() const {
	if (!examineText.empty()) {
		cout << examineText << "\n";
	}
	else {
		cout << "I see nothing special about " << name << ".\n";
	}

	if (!closed) {
		if (getIsContainer()) {
			if (getContains().empty()) {
				cout << getName() << " is empty.\n";
			}
			else {
				cout << getName() << " contains:\n";
				for (Entity* entity : getContains()) {
					displayContains(entity, 1);
				}
			}
		}
	}
	else {
		Lockable::Examine(name);
	}
}

bool Item::isPickable() const {
	return pickable;
}

const bool Item::getIsContainer() const {
	return isContainer;
}

TypesItems Item::getItemType() const {
	return itemType;
}

int Item::getDmg() const {
	return dmg;
}

void Item::setDmg(int newDmg) {
	dmg = newDmg;
}