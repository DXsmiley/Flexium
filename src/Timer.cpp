#include <Flexium/Timer.hpp>
#include <Flexium/Event.hpp>

namespace flx {

	void Timer::onUpdate() {
		if (isAlive() && event != nullptr) {
			if (mytime == 0) {
				event -> setWorld(getWorld());
				event -> trigger();
				event = nullptr;
				destroy();
			} else {
				mytime--;
			}
		}
	}

}