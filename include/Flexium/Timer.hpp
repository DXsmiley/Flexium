#ifndef TIMER_HPP
#define TIMER_HPP

#include <Flexium/Memory.hpp>
#include <Flexium/Object.hpp>

namespace flx {

	class Event;

	class Timer: public Object {

		private:

			unsigned int mytime;
			std::shared_ptr<Event> event;

		public:

			Timer(unsigned int t, std::shared_ptr<Event> e): mytime(t), event(e) {};
			virtual void onUpdate();
			virtual ~Timer() {};

	};

}

#endif