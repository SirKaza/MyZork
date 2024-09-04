#include "entity.h"
#include <iostream>
#include <string>

using namespace std;


Entity::Entity(const string& name, const string& description) 
	: name(name), description(description) {

	this->type = TypesEntities::Entity;
}


Entity::~Entity() {

}	


void Entity::Update() {

}


void Entity::Look() const {
	cout << name << "\n";
	cout << description << "\n";
}


void Entity::setContains(Entity* object) {
	contains.push_back(object);
}


list<Entity*> Entity::getContains() const {
	return contains;
}

const string& Entity::getName() const {
	return name;
}

const string& Entity::getDescription() const {
	return description;
}
