#include "item.h"

using namespace std;

Item::Item(const string& name, const string& description, const bool isContainer)
	: Entity(name, description, isContainer) {

	this->type = TypesEntities::Item;
}

Item::~Item() {

}



