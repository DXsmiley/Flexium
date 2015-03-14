#include <Flexium/ExtraEvents.hpp>
#include <Flexium/ConsoleMinimal.hpp>
#include <Flexium/World.hpp>

namespace flx {

	void EventPrint::onTrigger() {
		Console::Log << text << std::endl;
	}

	void EventCreate::onTrigger() {
		getWorld() -> instanceAdd(obj);
	}

	void EventDestroy::onTrigger() {
		obj -> destroy();
	}

	EventCompond::EventCompond(std::initializer_list<std::shared_ptr<Event> > il) {
		for (const auto& i : il) {
			events.push_back(i);
		}
	}

	void EventCompond::onTrigger() {
		for (unsigned int i = 0; i < events.size(); ++i) {
			events[i] -> trigger(world);
		}
	}

	EventCompond::~EventCompond() {
		
	}

}