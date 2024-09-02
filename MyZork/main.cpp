#include "main.h"
#include <iostream>
#include <string>
#include "world.h"

using namespace std;

int main() {
	string input;
	cout << "You are in a dark room. There is a door to the north.\n";
	cout << "What do you want to do?";
	
	getline(cin, input);

	if (input == "go north") {
		cout << "You enter a new room. It is brightly lit.\n";
	}
	else {
		cout << "You remain in the dark room.\n";
	}

	return 0;
}