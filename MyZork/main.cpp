#include "main.h"
#include <iostream>
#include <string>
#include "world.h"

using namespace std;

int main() {
	string input;

	World* myWorld = new World();
	
	cout << "Welcome to my Zork!\n";

	if (input == "go north") {
		cout << "You enter a new room. It is brightly lit.\n";
	}
	else {
		cout << "You remain in the dark room.\n";
	}

	return 0;
}