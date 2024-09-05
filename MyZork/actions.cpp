#include "actions.h"
#include <stdexcept>
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
	else if (command == "g") return Action::Repeat;
	else if (command == "use") return Action::Use;
	else throw invalid_argument("Unknown command: " + command);
}


string& toLowerCase(string& input) {
	transform(input.begin(), input.end(), input.begin(), tolower); 
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

