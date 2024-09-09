#include "exit.h"
#include "actions.h"
#include <string>
#include <iostream>

using namespace std;


Exit::Exit(const string& name, const string& description, Direction direction, Room* source, Room* destination, const string& examineText, bool canClose, bool closed, bool locked, const string& key)
	: Entity(name, description, examineText), Lockable(canClose, closed, locked, key), direction(direction), source(source), destination(destination) {

	this->type = TypesEntities::Exit;
}


Exit::~Exit() {

}

void Exit::Examine() const {
	if (!examineText.empty()) {
		cout << examineText << "\n";
	}
	else {
		cout << "I see nothing special about " << name << ".\n";
	}
	Lockable::Examine(name);
}


Direction Exit::getDirection() const {
	return direction;
}


Room* Exit::getSource() const {
	return source;
}


Room* Exit::getDestination() const {
	return destination;
}
