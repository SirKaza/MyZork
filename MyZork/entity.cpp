#include "entity.h"
#include <iostream>

using namespace std;


Entity::Entity(const string& name, const string& description) 
	: name(name), description(description) {

	this->type = TypesEntities::ENTITY;
}


Entity::~Entity() {

}	


void Entity::Update() {

}


void Entity::display() {
	cout << name << "\n";
	cout << description << "\n";
}


void Entity::setContains(Entity* object) {
	contains.push_back(object);
}


list<Entity*> Entity::getContains() {
	return contains;
}
