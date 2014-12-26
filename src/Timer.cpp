#include <Flexium/Timer.hpp>
#include <Flexium/Event.hpp>

namespace flx {

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

}