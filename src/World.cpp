#include <Flexium/World.hpp>
#include <Flexium/Window.hpp>
#include <Flexium/Input.hpp>
#include <Flexium/Console.hpp>

#include <algorithm>

namespace flx {

	class ObjectSorter {

		public:

			bool operator ()(const Object * const a, const Object * const b) const {
				return a -> getDepth() < b -> getDepth();
			}

	} object_sorter;

	Object * World::instanceAdd(Object * o) {
		instances.push_back(o);
		o -> registerWorld(id_counter++, this);
		o -> onCreate();
		return o;
	}

	bool World::simulate() {
		bool open = Window::getHandle() -> isOpen();
		//std::stringstream ss;
		//ss << "FPS: " << fpsGet(fps_clock.restart());
		//Window::getHandle() -> setTitle(ss.str());
		//Console::Log << "Tick" << std::endl;
		if (open) {
			Input::update();
			Window::getHandle() -> clear(::sf::Color::Black);
			std::stable_sort(instances.begin(), instances.end(), object_sorter);
			for (unsigned int i = 0; i < instances.size(); i++) {
				if (instances[i] -> isAlive() && instances[i] -> isActive()) {
					instances[i] -> onUpdate();
				}
			}
			std::stable_sort(instances.begin(), instances.end(), object_sorter);
			for (unsigned int i = 0; i < instances.size(); i++) {
				if (instances[i] -> isAlive() && instances[i] -> isActive()) {
					instances[i] -> onDraw();
				}
			}
			Window::getHandle() -> display();
		}
		return open;
	}

}