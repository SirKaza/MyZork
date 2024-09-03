#include "main.h"
#include <iostream>
#include <string>
#include "world.h"


using namespace std;

int main() {
	string input;
	string playerName;
	
	cout << "Welcome to my Zork!" << endl;
	cout << "What is your name? " << endl;
	getline(cin, playerName); // Ask for player name

	World* myWorld = new World(playerName); // Create World

	input = "look";
	myWorld->handleCommand(input);

	while (true) {

		getline(cin, input); // Player decision
		myWorld->handleCommand(input);

	}

	return 0;
}