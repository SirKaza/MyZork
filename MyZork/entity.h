#pragma once
#include <string>
#include <list>
#include "lockable.h"
#include "actions.h"

using namespace std;

class Entity
{
	public:
		Entity(const string& name, const string& description, const string& examineText = "");
		virtual ~Entity(); 

		virtual void Update();

		virtual void Look() const;
		virtual void Examine() const;

		Entity* findEntityByName(const string& entityName);
		Entity* findEntityByNameAndType(const string& entityName, const TypesEntities type);
		Entity* findEntityByNameAndTypes(const string& entityName, const set<TypesEntities>& types);
		void removeEntity(Entity* entity);

		void displayContains(const Entity* entity, int level) const;
		
		void setContains(Entity* object);
		list<Entity*> getContains() const;
		list<Entity*> getContainsByType(TypesEntities type) const;

		void setExamineText(const string& newExamineText);


		const string& getName() const;
		const string& getDescription() const;
		TypesEntities getType() const;

	protected:
		TypesEntities type;
		string name;
		string description;
		list<Entity*> contains; // Inventary (player), Room space and containers (chest)

		string examineText;
};

