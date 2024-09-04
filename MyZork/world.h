#pragma once
#include <list>
#include <string>

using namespace std;

class Entity;
class Player;

class World
{
	public:
		World(const string& playerName);
		~World();

		void handleCommand(string& input);

	private:
		list<Entity*> entities;
		Player* player;
		string lastInput; // Repeat case
};

