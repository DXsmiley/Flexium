#include <Flexium/Event.hpp>

namespace flx {

	World * Event::getWorld() {
		return world;
	}

	void Event::setWorld(World * w) {
		world = w;
	}

}