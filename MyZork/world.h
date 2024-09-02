#pragma once
#include <list>

using namespace std;

class Entity;

class World
{
	public:
		World();
		~World();

	private:
		list<Entity*> entities;
};

