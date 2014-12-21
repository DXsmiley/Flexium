#include "Event.hpp"

World * Event::getWorld() {
	return world;
}

void Event::setWorld(World * w) {
	world = w;
}