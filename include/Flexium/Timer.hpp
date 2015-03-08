#ifndef TIMER_HPP
#define TIMER_HPP

#include <Flexium/Memory.hpp>
#include <Flexium/Object.hpp>
#include <Flexium/Event.hpp>

namespace flx {

	class Timer: public Object {

		private:

			unsigned int mytime;
			flx::shared_ptr_autocast<Event> event;

		public:

			Timer(unsigned int t, flx::shared_ptr_autocast<Event> e): mytime(t), event(e) {};
			virtual void onUpdate();
			virtual ~Timer() {};

	};

}

#endif