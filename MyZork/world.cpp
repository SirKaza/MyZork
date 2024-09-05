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
	Room* parking = new Room("Parking", "You are in a parking lot in which there is only one car.", true, "The parking lot is dimly lit, and you can see a single car parked here. It's quite dusty, as if no one has visited in a while.");
	Room* forest = new Room("Forest", "You are in a forest next to a river.", true, "Tall trees surround you, their leaves whispering in the gentle breeze. The sound of the nearby river is soothing, and the ground is carpeted with soft moss.");
	Room* bunker = new Room("Bunker", "You are in the hall of the bunker.", true, "The bunker feels cold, dark and damp. Metal beams support the structure and there is a sinister atmosphere.");

	entities.push_back(parking);
	entities.push_back(forest);
	entities.push_back(bunker);

	// ---- Exits ----
	Exit* trail = new Exit("Trail", "Short dirt path.", Direction::East, parking, forest, false, "The dirt road is largely covered in grass, indicating that it has not been used for quite some time. You can barely see footprints leading east.");
	Exit* trail2 = new Exit("Trail", "Short dirt path.", Direction::West, forest, parking, false, "The dirt road is largely covered in grass, indicating that it has not been used for quite some time. You can barely see footprints leading west.");
	Exit* hatch = new Exit("Hatch", "Old metal hatch.", Direction::Down, forest, bunker, false, "The old metal hatch is heavily rusted, with a few faint scratches visible. It looks like it hasn't been opened in ages.");
	Exit* stairs = new Exit("Stairs", "Old stone stairs.", Direction::Up, bunker, forest, false, "The old stone stairs are worn and uneven. Some stones are chipped, and the surface feels cool to the touch.");

	entities.push_back(trail);
	entities.push_back(trail2);
	entities.push_back(hatch);
	entities.push_back(stairs);

	parking->setContains(trail);
	forest->setContains(trail2);
	forest->setContains(hatch);
	bunker->setContains(stairs);

	// ---- Player ----
	player = new Player(playerName, "An ambitious adventurer.", parking, true);
	entities.push_back(player);

	// ---- Items ----
	Item* keychain = new Item("Keychain", "There are 2 keys on the keychain, one is a car key and the other is unknown.", false, "The keychain is well-used, with two keys hanging from it. The car key is slightly larger than the other, which has a unique shape.");
	Item* keycard = new Item("Keycard", "An access card with a strange logo, it is quite dirty as if it had been lost a long time ago.", false, "This key card is covered in dirt and the logo is barely visible. It probably opens something old too.");
	Item* box = new Item("Box", "A small metal box.", true, "The small metal box is cold and heavy. It has intricate designs carved into its surface and a small, peculiarly shaped lock on the front.");

	parking->setContains(keychain);
	forest->setContains(keycard);
	bunker->setContains(box);
}

World::~World() {
	for (Entity* entity : entities) {
		if (entity != nullptr) {
			delete entity;
		}
	}
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

	if (action != Action::Repeat) { // Save last input
		lastInput = input;
	}

	switch (action) {
		case (Action::Look): // look room or player
			if (args.empty()) { // show room
				if (player->getLocation() != nullptr) {
					player->getLocation()->Look();
				}
			}
			else if (args.size() == 1) { // look object
				string playerName = player->getName();
				toLowerCase(playerName);
				if (args[0] == "me" || args[0] == "myself" || args[0] == playerName) {
					player->Look();
				}
				else {
					cout << "I don't understand what you want to look at." << endl;
				}
			}
			else {
				cout << "Too many things to look at." << endl;
			}
			break;

		case (Action::Go): // move through rooms
			if (args.empty() && command == "go") { 
				cout << "You'll have to say which compass direction to go in.\n";
			}
			else if (args.empty() && command != "go") { // cardinal points
				player->Go(command);
			}
			else if (args.size() == 1) { // go point
				player->Go(args[0]);
			}
			break;

		case Action::Take: // take items
			if (!args.empty()) {
				player->Take(args);
			}
			else {
				cout << "What do you want to take?\n";
			}
			break;

		case Action::Drop:
			if (!args.empty()) {
				player->Drop(args);
			}
			else {
				cout << "What do you want to drop?\n";
			}
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
			player->Inventory();
			break;

		case Action::Examine:
			if (!args.empty()) {
				player->Examine(args);
			}
			else {
				cout << "What do you want to examine?\n";
			}
			
			break;

		case Action::Put:
			if (args.size() > 1) {
				player->Put(args);
			}
			else if (args.size() == 1) {
				cout << "What do you want to put " << args[0] << " in?\n";
			}
			else {
				cout << "What do you want to put?\n";
			}
			break;

		case Action::Repeat:
			handleCommand(lastInput);
			break;

		case Action::Scream:
			cout << "Aaaarrrrgggghhhh!" << endl;
			break;

		case Action::Use:

			break;

		default:
			cout << "That's not a verb I recognise." << endl;
			break;
	}
}