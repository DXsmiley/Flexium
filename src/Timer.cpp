#include "Timer.hpp"
#include "Event.hpp"

void Timer::onUpdate() {
	if (isAlive() && event) {
		if (mytime == 0) {
			event -> setWorld(getWorld());
			event -> trigger();
			delete event;
			event = NULL;
			destroy();
		} else {
			mytime--;
		}
	}
}