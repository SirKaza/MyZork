#pragma once
#include <string>
#include <list>

using namespace std;

enum class TypesEntities {
	ENTITY,
	CREATURE,
	EXIT,
	ROOM,
	ITEM,
	PLAYER
};

class Entity
{
	public:
		Entity(const string& name, const string& description);
		virtual ~Entity(); // sons can overwrite

		void virtual Update();

		void virtual display();
		
		void setContains(Entity* object);
		list<Entity*> getContains();

	protected:
		TypesEntities type;
		string name;
		string description;
		list<Entity*> contains; // Inventary (player), Room space and containers (chest)
};

