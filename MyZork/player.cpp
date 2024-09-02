#include "player.h"
#include <string>

using namespace std;

Player::Player(const string name, const string description, Room* location) 
	: Creature(name, description, location) {

	this->type = TypesEntities::PLAYER;
}

Player::~Player() {

}