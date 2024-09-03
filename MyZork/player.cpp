#include "player.h"
#include "room.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player(const string& name, const string& description, Room* location) 
	: Creature(name, description, location) {

	this->type = TypesEntities::PLAYER;
}

Player::~Player() {

}

void Player::display() {
	cout << name << "\n";
	cout << description << "\n";

	if (location != nullptr) {
		cout << location->getName() << "\n";
	}
	else {
		cout << "Unknown location" << "\n";
	}
}