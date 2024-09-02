#include "world.h"
#include "entity.h"
#include "room.h"
#include "exit.h"

using namespace std;

World::World() {
	Room* parking = new Room("Parking", "You are in a parking lot in which there is only one car.");
	Room* forest = new Room("Forest", "You are in a forest next to a river.");
	Room* bunker = new Room("Bunker", "You are in the hall of the bunker.");

	entities.push_back(parking);
	entities.push_back(forest);
	entities.push_back(bunker);

	Exit* exit1 = new Exit("Trail", "Short dirt path.", Direction::EAST, parking, forest);
	Exit* exit2 = new Exit("Hatch", "Old metal hatch.", Direction::SOUTH, forest, bunker);

	entities.push_back(exit1);
	entities.push_back(exit2);
}

World::~World() {

}