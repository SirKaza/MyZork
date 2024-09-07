#include "exit.h"
#include "actions.h"
#include <string>
#include <iostream>

using namespace std;


Exit::Exit(const string& name, const string& description, Direction direction, Room* source, Room* destination, bool isContainer, const string& examineText, const bool canClose, bool closed, bool locked)
	: Entity(name, description, isContainer, examineText), direction(direction), source(source), destination(destination), canClose(canClose), closed(closed) , locked(locked) {

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

bool Exit::isClosed() const {
	return closed;
}

bool Exit::isLocked() const {
	return locked;
}

const bool Exit::getCanClose() const {
	return canClose;
}

void Exit::inverseClosed() {
	if (closed) {
		closed = false;
	}
	else {
		closed = true;
	}
}

void Exit::inverseLocked() {
	if (locked) {
		locked = false;
	}
	else {
		locked = true;
	}
}