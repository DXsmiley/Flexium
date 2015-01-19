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

			std::shared_ptr<Object> p;

		public:

			CallEventInstanceAdded(std::shared_ptr<Object> x): p(x) {};
			void operator()(std::shared_ptr<Object> o) const {
				o -> onInstanceAdded(p);
			}

	};

	class CallEventUpdate {

		public:

			void operator()(std::shared_ptr<Object> o) const {
				o -> onUpdate();
			}

	};

	class CallEventDraw {

		public:

			void operator()(std::shared_ptr<Object> o) const {
				o -> onDraw();
			}

	};

	class ObjectSorter {

		public:

			bool operator ()(const std::shared_ptr<Object> a, const std::shared_ptr<Object> b) const {
				return a && b && a -> getDepth() < b -> getDepth();
			}

	} object_sorter;

	template <typename T>
	void callEvent(std::vector<std::shared_ptr<Object> >& vec, const T action) {
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
		my_clock.restart();
	}

	std::shared_ptr<Object> World::instanceAdd(std::shared_ptr<Object> o) {
		o -> registerWorld(id_counter++, this);
		o -> onCreate();
		// signal to existing objects that this object has been added (THIS HAS NOT BEEN THOUGHROUGLY TESTED)
		instances.push_back(o);
		callEvent(instances_on_instance_added, CallEventInstanceAdded(o));
		instances_on_instance_added.push_back(o);
		instances_on_update.push_back(o);
		instances_on_draw.push_back(o);
		return o;
	}

	std::shared_ptr<Object> World::instanceAdd(Object * ptr) {
		return instanceAdd(std::shared_ptr<Object>(ptr));
	}

	void World::instanceAdd(std::initializer_list<Object *> l) {
		for (auto i : l) {
			instanceAdd(i);
		}
	}

	bool World::simulate() {
		bool open = Window::getHandle() -> isOpen();
		if (open) {
			Input::update();
			Window::clear();
			callEvent(instances_on_update, CallEventUpdate());
			callEvent(instances_on_draw, CallEventDraw());
			Window::display();
			sf::Time elapsed = my_clock.restart();
			double time_to_sleep = std::max(0.01, (1.0 / 60.0) - elapsed.asSeconds());
			sf::sleep(sf::seconds(time_to_sleep));
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