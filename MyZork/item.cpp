#include "item.h"

using namespace std;

Item::Item(const string& name, const string& description, bool isContainer, const string& examineText, bool canClose, bool closed, bool locked)
	: Entity(name, description, isContainer, examineText), Lockable(canClose, closed, locked) {

	this->type = TypesEntities::Item;
}

Item::~Item() {

}



