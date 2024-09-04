#include "world.h"
#include "entity.h"
#include "room.h"
#include "exit.h"
#include "creature.h"
#include "player.h"
#include "actions.h"
#include "item.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

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

	// ---- Items ----
	Item* car_key = new Item("Car key", "A car key which looks familiar to you.");
	Item* keycard = new Item("Keycard", "An access card with a strange logo, it is quite dirty as if it had been lost a long time ago.");

	parking->setContains(car_key);
	forest->setContains(keycard);
}

World::~World() {

}

void World::handleCommand(string& input) {
	istringstream iss(input);
	string command;
	vector<string> args;

	iss >> command;  // First token as a command
	toLowerCase(command);

	string arg;
	while (iss >> arg) {
		args.push_back(arg);  // Rest as arguments
	}

	for (string& arg : args) { // args lowercase
		toLowerCase(arg);
	}

	Action action;

	try {
		action = stringToAction(command);
	}
	catch (const invalid_argument& e) {
		cout << e.what() << endl; // In case of error
		return;
	}

	switch (action) {
		case (Action::Look): 
			if (args.empty()) { // show room
				if (player->getLocation() != nullptr) {
					player->getLocation()->display();
				}
			}
			else if (args.size() == 1) { // look object
				string playerName = player->getName();
				toLowerCase(playerName);
				if (args[0] == "me" || args[0] == "myself" || args[0] == playerName) {
					player->display();
				}
				else {
					cout << "I don't understand what you want to look at." << endl;
				}
			}
			else {
				cout << "Too many things." << endl;
			}
			break;

		case (Action::Go):

			break;

		case Action::Take:

			break;

		case Action::Drop:

			break;

		case Action::Quit: // User wants to quit
			cout << "Are you sure you want to quit? (yes/no): " << endl;
			getline(cin, command); // Ask for confirmation

			if (command == "yes" || command == "y") {
				cout << "Thank you for playing! Goodbye!" << endl;
				exit(0); // Exit the loop
			}
			break;

		case Action::Inventory:

			break;

		case Action::Examine:

			break;

		case Action::Put:

			break;

		case Action::Use:

			break;

		default:
			cout << "That's not a verb I recognise." << endl;
			break;
	}
}