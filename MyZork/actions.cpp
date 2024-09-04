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

