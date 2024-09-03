#include "actions.h"
#include <stdexcept>
#include <algorithm>

using namespace std;

Action stringToAction(const string& input) {
	string command = input;
	transform(command.begin(), command.end(), command.begin(), tolower); // Lowercase the command

	if (command == "look" || command == "l") return Action::Look;
	else if (command == "go") return Action::Go;
	else if (command == "take") return Action::Take;
	else if (command == "drop") return Action::Drop;
	else if (command == "quit" || command == "q") return Action::Quit;
	else if (command == "inventory" || command == "i") return Action::Inventory;
	else if (command == "examine") return Action::Examine;
	else if (command == "use") return Action::Use;
	else throw invalid_argument("Unknown command: " + command);
}

