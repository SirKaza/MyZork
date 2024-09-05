#include "item.h"

using namespace std;

Item::Item(const string& name, const string& description, const bool isContainer, const string& examineText)
	: Entity(name, description, isContainer, examineText) {

	this->type = TypesEntities::Item;
}

Item::~Item() {

}



