#include "actions.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

Action stringToAction(const string& command) {
	if (command == "look" || command == "l") return Action::Look;
	else if (command == "go" || command == "north" || command == "n" || command == "south" || command == "s" || command == "east" || command == "e" || command == "west" || command == "w" || command == "up" || command == "u" || command == "down" || command == "d") return Action::Go;
	else if (command == "take" || command == "get" || command == "grab" || command == "pick") return Action::Take;
	else if (command == "drop" || command == "throw") return Action::Drop;
	else if (command == "quit" || command == "q") return Action::Quit;
	else if (command == "inventory" || command == "i") return Action::Inventory;
	else if (command == "examine") return Action::Examine;
	else if (command == "put") return Action::Put;
	else if (command == "open") return Action::Open;
	else if (command == "close") return Action::Close;
	else if (command == "lock") return Action::Lock;
	else if (command == "unlock") return Action::Unlock;
	else if (command == "equip") return Action::Equip;
	else if (command == "unequip") return Action::Unequip;
	else if (command == "attack") return Action::Attack;
	else if (command == "g") return Action::Repeat;
	else if (command == "shout" || command == "yell" || command == "scream" || command == "" || command == "zork" || command == "jump") return Action::Extra;
	else if (command == "help" || command == "h") return Action::Help;
	else throw invalid_argument("That's not a verb I recognise.");
}

string toLowerCase(const string& input) {
	string result = input; 
	transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return tolower(c); });
	return result;
}

string& toLowerCaseModify(string& input) {
	transform(input.begin(), input.end(), input.begin(),
		[](unsigned char c) { return tolower(c); });
	return input;
}

Direction stringToDirection(const string& direction) {
	if (direction == "north" || direction == "n") return Direction::North;
	else if (direction == "south" || direction == "s") return Direction::South;
	else if (direction == "east" || direction == "e") return Direction::East;
	else if (direction == "west" || direction == "w") return Direction::West;
	else if (direction == "up" || direction == "u") return Direction::Up;
	else if (direction == "down" || direction == "d") return Direction::Down;
	else return Direction::None;
}

string directionToString(Direction direction) {
	switch (direction) {
		case Direction::North: return "north";
		case Direction::South: return "south";
		case Direction::East: return "east";
		case Direction::West: return "west";
		case Direction::Up: return "up";
		case Direction::Down: return "down";
		default: return "uknown";
		break;
	}
}

void printHelp() {
	cout << "===== HELP MENU =====\n";
	cout << "You can use the following commands:\n";
	cout << "  - look / l: Look around the current room or player.\n";
	cout << "    Example: 'look' to look room or 'look (me/myself/name of player)' to look player.\n";
	cout << "  - go [direction]: Move in a direction (north, south, east, west, up, down).\n";
	cout << "    Example: 'go north' or 'north' or 'n'.\n";
	cout << "  - take / get / pick / grab [item]: Pick up an item from the room. Also can take all items in room. \n";
	cout << "    Example: 'take keycard' or 'take all/everything'.\n";
	cout << "  - take / get / pick / grab [item] from/of [container]: Pick up an item from a container. \n";
	cout << "    Example: 'take keycard from leaves'.\n";
	cout << "  - drop [item]: Drop an item from your inventory. Also can drop all items in room.\n";
	cout << "    Example: 'drop keychain' or 'drop all/everything'.\n";
	cout << "  - examine [something]: Get a detailed description of something.\n";
	cout << "    Example: 'examine leaves'.\n";
	cout << "  - put [item] in [container]: Put an item into a container.\n";
	cout << "    Example: 'put keycard in box'.\n";
	cout << "  - open [something]: Open an exit or container.\n";
	cout << "    Example: 'open box'.\n";
	cout << "  - close [something]: Close an exit or container.\n";
	cout << "    Example: 'close box'.\n";
	cout << "  - lock [something] with [item]: Lock something using a item as a key.\n";
	cout << "    Example: 'lock box with keychain'.\n";
	cout << "  - unlock [something] with [item]: Unlock something using a item as a key.\n";
	cout << "    Example: 'unlock box with keychain'.\n";
	cout << "  - equip [item]: Equip an item, such as a weapon or shield.\n";
	cout << "    Example: 'equip sword'.\n";
	cout << "  - unequip [item]: Unequip an currently equipped item.\n";
	cout << "    Example: 'unequip sword'.\n";
	cout << "  - attack [someone]: Attack an enemy.\n";
	cout << "    Example: 'attack ogre'.\n";
	cout << "  - inventory / i: Check your inventory and equipment.\n";
	cout << "  - quit / q: Quit the game.\n";
	cout << "  - repeat: Repeats the last command you entered.\n";
	cout << "  - shout / yell / scream: Express your feelings.\n";
	cout << "  - jump / zork: Perform a fun, silly action.\n";
	cout << "  - help / h: Show this help menu.\n";
	cout << "======================\n";
}

