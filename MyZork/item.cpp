#include "item.h"

using namespace std;

Item::Item(const string& name, const string& description)
	: Entity(name, description) {

	this->type = TypesEntities::Item;
}

Item::~Item() {

}