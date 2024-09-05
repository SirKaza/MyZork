#include "exit.h"
#include "actions.h"
#include <string>

using namespace std;


Exit::Exit(const string& name, const string& description, Direction direction, Room* source, Room* destination, const bool isContainer)
	: Entity(name, description, isContainer), direction(direction), source(source), destination(destination) {

	this->type = TypesEntities::Exit;
}


Exit::~Exit() {

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