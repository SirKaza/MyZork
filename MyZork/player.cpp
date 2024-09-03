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