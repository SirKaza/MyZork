#include "main.h"
#include <iostream>
#include <string>
#include "world.h"


using namespace std;

int main() {
	string input;
	string playerName;
	
	cout << "Welcome to my Zork!\n";
	cout << "What is your name?";
	getline(cin, playerName); // Ask for player name

	World* myWorld = new World(playerName); // Create World

	while (true) {

		// display

		getline(cin, input); // Player decision

		if (input == "quit" || input == "q") { // Check if the user wants to quit
			cout << "Are you sure you want to quit? (yes/no): ";
			getline(cin, input); // Ask for confirmation

			if (input == "yes" || input == "y") {
				cout << "Thank you for playing! Goodbye!\n";
				break; // Exit the loop
			}
			else {
				getline(cin, input);
			}
		}
		else {
			myWorld->handleCommand(input);
		}

	}

	return 0;
}