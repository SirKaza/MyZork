#include "item.h"
#include <iostream>

using namespace std;

Item::Item(const string& name, const string& description, bool pickable, bool isContainer, const string& examineText, bool canClose, bool closed, bool locked, const string& key)
	: Entity(name, description, examineText), Lockable(canClose, closed, locked, key), pickable(pickable), isContainer(isContainer) {
	
	this->type = TypesEntities::Item;
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
					displayContains(entity, 0);
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


