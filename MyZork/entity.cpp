#include "entity.h"
#include "actions.h"
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


Entity* Entity::findEntityByNameAndType(const string& entityName, TypesEntities type) {
	string name;
	for (Entity* entity : contains) {
		if (entity->getType() == type) {
			name = entity->getName();
			if (toLowerCase(name) == entityName) {
				return entity;
			}
		}
	}
	return nullptr;
}

void Entity::removeEntity(Entity* entity) {
	contains.remove(entity);
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

TypesEntities Entity::getType() const {
	return type;
}

void Entity::displayContains(const Entity* entity, int level) const {
	for (int i = 0; i < level; ++i) {
		cout << " ";
	}
	cout << entity->getName() << "\n";

	if (!entity->getContains().empty()) { // item inside
		for (const Entity* inside : entity->getContains()) {
			displayContains(inside, level + 1); // recursion through items inside
		}
	}
}
