#include "exit.h"
#include <string>

using namespace std;

Exit::Exit(const string name, const string description, Direction direction, Room* source, Room* destination) 
	: Entity(name, description), direction(direction), source(source), destination(destination) {

	this->type = TypesEntities::EXIT;
}

Exit::~Exit() {

}