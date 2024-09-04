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
		Entity(const string& name, const string& description);
		virtual ~Entity(); // sons can overwrite

		virtual void Update();

		virtual void Look() const;
		
		void setContains(Entity* object);
		list<Entity*> getContains() const;

		const string& getName() const;
		const string& getDescription() const;

	protected:
		TypesEntities type;
		string name;
		string description;
		list<Entity*> contains; // Inventary (player), Room space and containers (chest)
};

