#include "entity.h"
#include "actions.h"
#include "item.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

Entity::Entity(const string& name, const string& description, const string& examineText)
	: name(name), description(description), examineText(examineText){

	this->type = TypesEntities::Entity;
}

Entity::~Entity() {

}	

void Entity::Update() {

}

void Entity::Look() const {
	cout << name << ": " << description <<"\n";
}

void Entity::Examine() const {
	if (!examineText.empty()) {
		cout << examineText << "\n";
	}
	else {
		cout << "I see nothing special about " << name << ".\n";
	}
}

Entity* Entity::findEntityByName(const string& entityName) {
	string name;
	for (Entity* entity : contains) {
		name = entity->getName();
		if (toLowerCase(name) == entityName) {
			return entity;
		}
	}
	return nullptr;

}

Entity* Entity::findEntityByNameAndType(const string& entityName, const TypesEntities type) {
	string name;
	for (Entity* entity : contains) {
		name = entity->getName();
		if (toLowerCase(name) == entityName) { // match name
			if (entity->getType() == type) { // match in type
				return entity;
			}
		}
	}
	return nullptr;
}

Entity* Entity::findEntityByNameAndTypes(const string& entityName, const set<TypesEntities>& types) {
	string name;
	for (Entity* entity : contains) {
		name = entity->getName();
		if (toLowerCase(name) == entityName) { // match name
			if (types.find(entity->getType()) != types.end()) { // match in type
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

list<Entity*> Entity::getContainsByType(TypesEntities type) const {
	list<Entity*> filteredEntities;

	for (Entity* entity : contains) {
		if (entity->getType() == type) {
			filteredEntities.push_back(entity);
		}
	}
	return filteredEntities;
}

void Entity::setExamineText(const string& newExamineText) {
	examineText = newExamineText;
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

void Entity::displayContains(Entity* entity, int level) const {
	for (int i = 0; i < level; ++i) {
		cout << " ";
	}
	cout << entity->getName() << "\n";

	if (Item* item = dynamic_cast<Item*>(entity)) {
		if (!item->isClosed()) { // if item is not closed print inside
			if (!item->getContains().empty()) { // item inside
				for (Entity* inside : item->getContains()) {
					displayContains(inside, level + 1); // recursion through items inside
				}
			}
		}
	}
}
