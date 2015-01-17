#include <Flexium/World.hpp>
#include <Flexium/Flexium.hpp>
#include <Flexium/Window.hpp>
#include <Flexium/Input.hpp>
#include <Flexium/Console.hpp>
#include <Flexium/Object.hpp>

#include <algorithm>

namespace flx {

	class CallEventInstanceAdded {

		private:

			Object * p;

		public:

			CallEventInstanceAdded(Object * x): p(x) {};
			void operator()(Object * o) const {
				o -> onInstanceAdded(p);
			}

	};

	class CallEventUpdate {

		public:

			void operator()(Object * o) const {
				o -> onUpdate();
			}

	};

	class CallEventDraw {

		public:

			void operator()(Object * o) const {
				o -> onDraw();
			}

	};

	class ObjectSorter {

		public:

			bool operator ()(const Object * const a, const Object * const b) const {
				return a != nullptr && b != nullptr && a -> getDepth() < b -> getDepth();
			}

	} object_sorter;

	template <typename T>
	void callEvent(std::vector<Object *>& vec, const T action) {
		std::stable_sort(vec.begin(), vec.end(), object_sorter);
		int last = 0;
		for (unsigned int i = 0; i < vec.size(); ++i) {
			try {
				if (vec[i] -> isAlive() && vec[i] -> isActive()) {
					action(vec[i]);
				}
				vec[last] = vec[i];
				++last;
			} catch (const FlexiumExceptionNotImplemented& e) {
				vec[i] = nullptr;
			}
		}
		vec.resize(last);
	}


	World::World() {
		id_counter = 0;
		trigger_update = true;
		trigger_draw = true;
	}

	Object * World::instanceAdd(Object * o) {
		instances.push_back(o);
		o -> registerWorld(id_counter++, this);
		o -> onCreate();
		// signal to existing objects that this object has been added (THIS HAS NOT BEEN THOUGHROUGLY TESTED)
		callEvent(instances_on_instance_added, CallEventInstanceAdded(o));
		instances_on_instance_added.push_back(o);
		instances_on_update.push_back(o);
		instances_on_draw.push_back(o);
		return o;
	}

	void World::instanceAdd(std::initializer_list<Object *> l) {
		for (auto i : l) {
			instanceAdd(i);
		}
	}

	bool World::simulate() {
		bool open = Window::getHandle() -> isOpen();
		//std::stringstream ss;
		//ss << "FPS: " << fpsGet(fps_clock.restart());
		//Window::getHandle() -> setTitle(ss.str());
		//Console::Log << "Tick" << std::endl;
		if (open) {
			Input::update();
			Window::clear();
			callEvent(instances_on_update, CallEventUpdate());
			callEvent(instances_on_draw, CallEventDraw());
			// std::stable_sort(instances.begin(), instances.end(), object_sorter);
			// for (unsigned int i = 0; i < instances.size(); i++) {
			// 	if (instances[i] -> isAlive() && instances[i] -> isActive() && (trigger_update || instances[i] -> isMeta())) {
			// 		instances[i] -> onUpdate();
			// 	}
			// }
			// std::stable_sort(instances.begin(), instances.end(), object_sorter);
			// for (unsigned int i = 0; i < instances.size(); i++) {
			// 	if (instances[i] -> isAlive() && instances[i] -> isActive() && (trigger_draw || instances[i] -> isMeta())) {
			// 		instances[i] -> onDraw();
			// 	}
			// }
			Window::display();
		}
		return open;
	}

	bool World::getTriggerUpdate() {
		return trigger_update;
	}

	bool World::getTriggerDraw() {
		return trigger_draw;
	}

	void World::setTriggerUpdate(bool t) {
		trigger_update = t;
	}

	void World::setTriggerDraw(bool t) {
		trigger_draw = t;
	}


}