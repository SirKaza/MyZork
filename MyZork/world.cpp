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
	Room* picnic = new Room("Picnic", "You are in a sunny picnic area surrounded by trees that provide some shade.", "A wooden picnic table is set up under a shady tree. The grass around is quite high, as if no one has used the picnic in a long time.");
	Room* parking = new Room("Parking", "You are in a parking lot in which there is only one car parked.", "The parking lot is dimly lit, and you can see a single car parked in a corner.");
	Room* forest = new Room("Forest", "You are in a forest next to a river.", "Tall trees surround you, their leaves whispering in the gentle breeze. The sound of the nearby river is soothing, and the ground is carpeted with leaves.");
	Room* laboratory = new Room("Laboratory", "You are in a high-tech laboratory.", "The laboratory is full of advanced equipment and the air smells of chemicals. It is cold and it feels like very important experiments are being carried out here.");
	Room* arena = new Room("Arena", "You are in a vast arena filled with sand and surrounded by walls.", "The sand is extensive, with sand under your feet and stone walls surrounding you. Faint marks can be seen in the sand, hinting at possible previous fights.");

	// ---- Items ----
	Item* keychain = new Item("Keychain", "There are 2 keys on the keychain, one is a car key and the other is unknown.", true, false, "The keychain is well-used, with two keys hanging from it. The car key is slightly larger than the other, which has a unique shape.");
	Item* keycard = new Item("Keycard", "An access card with a strange logo, it is quite dirty as if it had been lost a long time ago.", true, false, "This key card is covered in dirt and the logo is barely visible. It probably opens a door.");
	Item* box = new Item("Box", "A small metal box.", true, true, "The small metal box is cold and heavy. It has intricate designs carved into its surface and a small, peculiarly shaped lock on the front.", TypesItems::Normal, true, true, true, keychain->getName());
	Item* sword = new Item("Sword", "A long metal sword.", true, false, "", TypesItems::Weapon);
	Item* shield = new Item("Shield", "A small metal shield.", true, false, "", TypesItems::Shield);
	Item* club = new Item("Club", "A big wooden club.", true, false, "", TypesItems::Weapon);
	sword->setDmg(4);
	shield->setDmg(-2);
	club->setDmg(3);

	Item* leaves = new Item("Leaves", "There is a pile of leaves grouped near one of the trees.", false, true, "You carefully move the leaves aside and uncover a keycard. It's an access card with a strange logo.");
	Item* table = new Item("Table", "An old wooden table, worn by time and use.", false, true, "You look closely at the table and discover a keychain in one of the fissure of the table.");
	Item* car = new Item("Car", "A dusty old car, parked here for what seems like forever. The paint is chipped and the tires are flat. It looks like it hasn't been driven in a long time.", false, true, "", TypesItems::Normal, true, true, true, keychain->getName());

	// ---- Exits ----
	Exit* road = new Exit("Road", "A paved road.", Direction::North, parking, picnic, "The road is well-maintained and lined with trees, making it a pleasant walk to the north.");
	Exit* road2 = new Exit("Road", "A paved road.", Direction::South, picnic, parking, "The road is well-maintained and lined with trees, making it a pleasant walk to the south.");
	Exit* trail = new Exit("Trail", "Short dirt path.", Direction::East, parking, forest, "The dirt road is largely covered in grass, indicating that it has not been used for quite some time. You can barely see footprints leading east.");
	Exit* trail2 = new Exit("Trail", "Short dirt path.", Direction::West, forest, parking, "The dirt road is largely covered in grass, indicating that it has not been used for quite some time. You can barely see footprints leading west.");
	Exit* hatch = new Exit("Hatch", "Old metal hatch.", Direction::Down, forest, laboratory, "The old metal hatch is heavily rusted, with a few faint scratches visible. It looks like it hasn't been opened in ages.", true, true);
	Exit* stairs = new Exit("Stairs", "Old stone stairs.", Direction::Up, laboratory, forest, "The old stone stairs are worn and uneven. Some stones are chipped, and the surface feels cool to the touch.");
	Exit* door = new Exit("Door", "A big metal door with a card reader on the side.", Direction::West, laboratory, arena,  "You examine the large metal door closely. The word 'danger' is written on it. It is facing west, who knows what lies on the other side for someone to write that?", true, true, true, keycard->getName());
	Exit* door2 = new Exit("Door", "A big metal door with a card reader on the side.", Direction::East, arena, laboratory, "", true, false, false, keycard->getName()); // open

	parking->setContains(road);
	picnic->setContains(road2);
	parking->setContains(trail);
	forest->setContains(trail2);
	forest->setContains(hatch);
	laboratory->setContains(stairs);
	laboratory->setContains(door);
	arena->setContains(door2);

	// ---- Creatures ----
	player = new Player(playerName, "An ambitious adventurer.", parking);
	Creature* boss = new Creature("Ogre", "A huge, burly creature with thick green skin and a menacing presence.", arena, "It seems dangerous, better be well prepared before acting.");
	
	// setContains items
	table->setContains(keychain);
	picnic->setContains(table);

	car->setContains(sword);
	parking->setContains(car);

	leaves->setContains(keycard);
	forest->setContains(leaves);

	box->setContains(shield);
	laboratory->setContains(box);

	boss->setWeapon(club);
	arena->setContains(boss);

	entities.push_back(picnic);
	entities.push_back(parking);
	entities.push_back(forest);
	entities.push_back(laboratory);
	entities.push_back(arena);
	entities.push_back(player); 
}

World::~World() {
	for (Entity* entity : entities) {
		if (entity != nullptr) {
			cout << "Delete " << entity->getName() << " from World." << endl;
			delete entity;
		}
	}
	entities.clear();
}

void World::handleCommand(string& input, bool& gameEnded) {
	istringstream iss(input);
	string command;
	vector<string> args;

	iss >> command;  // First token as a command
	toLowerCaseModify(command);

	string arg;
	while (iss >> arg) {
		args.push_back(arg);  // Rest as arguments
	}

	for (string& arg : args) { // args lowercase
		toLowerCaseModify(arg);
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

	bool move = false;
	switch (action) {
		case (Action::Look): // look room or player
			if (args.empty()) { // show room
				if (player->getLocation() != nullptr) {
					player->getLocation()->Look();
				}
			}
			else if (args.size() == 1) { // look player
				if (args[0] == "me" || args[0] == "myself" || args[0] == toLowerCase(player->getName())) {
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
			
			if (args.empty() && command == "go") { // go [none]
				cout << "You'll have to say which compass direction to go in.\n";
			}
			else if (args.empty() && command != "go") { // cardinal points
				move =  player->Go(command);
			}
			else if (args.size() == 1) { // go point
				move = player->Go(args[0]);
			}
			else {
				cout << "You can only move in one direction at a time.\n";
			}

			if (move) {
				player->getLocation()->Look();
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
				cout << "Thanks " << player->getName() << " for playing! Goodbye!" << endl;
				gameEnded = true;
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
				cout << "What do you want to examine?" << endl;
			}
			
			break;

		case Action::Put:
			if (args.size() > 1) {
				player->Put(args);
			}
			else if (args.size() == 1) {
				cout << "What do you want to put " << args[0] << " in?" << endl;
			}
			else {
				cout << "What do you want to put?" << endl;
			}
			break;

		case Action::Open:
			if (!args.empty()) {
				player->Open(args);
			}
			else {
				cout << "What do you want to open?" << endl;
			}
			break;

		case Action::Close:
			if (!args.empty()) {
				player->Close(args);
			}
			else {
				cout << "What do you want to close?" << endl;
			}
			break;


		case Action::Lock:
			if (!args.empty()) {
				player->Lock(args);
			}
			else {
				cout << "What do you want to lock?" << endl;
			}
			break;

		case Action::Unlock:
			if (!args.empty()) {
				player->Unlock(args);
			}
			else {
				cout << "What do you want to unlock?" << endl;
			}
			break;  
			
		case Action::Equip:
			if (!args.empty()) {
				player->Equip(args);
			}
			else {
				cout << "What do you want to equip?" << endl;
			}
			break; 
			
		case Action::Unequip:
			if (!args.empty()) {
				player->Unequip(args);
			}
			else {
				cout << "What do you want to unequip?" << endl;
			}
			break;

		case Action::Attack:
			if (!args.empty()) {
				player->Attack(args, gameEnded);
			}
			else {
				cout << "What do you want to attack?" << endl;
			}
			break;

		case Action::Repeat:
			handleCommand(lastInput, gameEnded);
			break;

		case Action::Extra:
			if (command == "shout" || command == "yell" || command == "scream") {
				cout << "Aaaarrrrgggghhhh!" << endl;
			}
			else if (command == "") {
				cout << "I beg your pardon?" << endl;
			}
			else if (command == "zork") {
				cout << "At your service!" << endl;
			}
			else if (command == "jump") {
				cout << "Are you proud of yourself?" << endl;
			}
			break;

		case Action::Help:
			printHelp();
			break;

		default:
			cout << "That's not a verb I recognise." << endl;
			break;
	}
}