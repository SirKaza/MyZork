#include "room.h"
#include <string>

using namespace std;

Room::Room(const string name, const string description) 
	: Entity(name, description) {

	this->type = TypesEntities::ROOM;
}

Room::~Room() {

}