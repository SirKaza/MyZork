#include "exit.h"
#include "actions.h"
#include <string>
#include <iostream>

using namespace std;


Exit::Exit(const string& name, const string& description, Direction direction, Room* source, Room* destination, bool isContainer, const string& examineText, bool canClose, bool closed, bool locked)
	: Entity(name, description, isContainer, examineText), Lockable(canClose, closed, locked), direction(direction), source(source), destination(destination) {

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

	//cout << "It seems like " << name << " leads to " << directionToString(direction) << ".\n";

	if (canClose) {
		string state;
		if (locked) { // if locked is closed
			state = "locked";
		}
		else if (!locked && closed) { // unlocked & closed
			state = "closed";
		}
		else { // opened
			state = "opened";
		}
		cout << "Looking closely, you notice that " << name << " is " << state << ".\n";
	}
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
