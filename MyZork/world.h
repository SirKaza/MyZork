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
		virtual ~World();

		void handleCommand(string& input, bool& gameEnded);

	private:
		list<Entity*> entities;
		Player* player;

		string lastInput; // Repeat case
};

