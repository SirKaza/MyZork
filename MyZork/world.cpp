#include "world.h"
#include "entity.h"
#include "room.h"
#include "exit.h"
#include "player.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

World::World(const string& playerName) {
	// ---- Rooms ----
	Room* parking = new Room("Parking", "You are in a parking lot in which there is only one car.");
	Room* forest = new Room("Forest", "You are in a forest next to a river.");
	Room* bunker = new Room("Bunker", "You are in the hall of the bunker.");

	entities.push_back(parking);
	entities.push_back(forest);
	entities.push_back(bunker);

	// ---- Exits ----
	Exit* exit1 = new Exit("Trail", "Short dirt path.", Direction::EAST, parking, forest);
	Exit* exit2 = new Exit("Hatch", "Old metal hatch.", Direction::SOUTH, forest, bunker);

	entities.push_back(exit1);
	entities.push_back(exit2);

	// ---- Player ----
	player = new Player(playerName, "An ambitious adventurer.", parking);
	entities.push_back(player);
}

World::~World() {

}

void World::handleCommand(string& input) {
	istringstream iss(input);
	string command;
	vector<string> args;

	iss >> command;  // First token as a command

	string arg;
	while (iss >> arg) {
		args.push_back(arg);  // Rest as arguments
	}

	switch (args.size()) {
		case 0:
			if (command == "look") {
				player->display();
			}
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			cout << "Unknown command." << endl;
			break;
	}
}