#pragma once
#include <string>
#include <list>

using namespace std;

enum class TypesEntities {
	Entity,
	Creature,
	Exit,
	Room,
	Item,
	Player
};

class Entity
{
	public:
		Entity(const string& name, const string& description, const bool isContainer);
		virtual ~Entity(); // sons can overwrite

		virtual void Update();

		virtual void Look() const;

		Entity* findEntityByNameAndType(const string& entityName, TypesEntities type);
		void removeEntity(Entity* entity);

		void displayContains(const Entity* entity, int level) const;
		
		void setContains(Entity* object);
		list<Entity*> getContains() const;
		list<Entity*> getContainsByType(TypesEntities type) const;

		const bool getIsContainer() const;
		const string& getName() const;
		const string& getDescription() const;
		TypesEntities getType() const;

	protected:
		TypesEntities type;
		string name;
		string description;
		list<Entity*> contains; // Inventary (player), Room space and containers (chest)

		const bool isContainer; // flag for entities that are able to use contains
};

