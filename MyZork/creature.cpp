#include "creature.h"
#include <string>

using namespace std;

Creature::Creature(const string& name, const string& description, Room* location)
	: Entity(name, description), location(location) {

	this->type = TypesEntities::CREATURE;
}

Creature::~Creature() {

}