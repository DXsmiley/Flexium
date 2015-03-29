#ifndef TIMER_HPP
#define TIMER_HPP

#include <Flexium/Memory.hpp>
#include <Flexium/Object.hpp>
#include <Flexium/Event.hpp>

namespace flx {


	/**
		Triggers an event after a certain number of frames.
	*/
	class Timer: public Object {

		private:

			unsigned int mytime;
			flx::shared_ptr_autocast<Event> event;

		public:

			/**
				Create a new timer.
				\param time The number of frames before the event is triggered.
				\param event The event to trigger.
			*/
			Timer(unsigned int time, flx::shared_ptr_autocast<Event> event): mytime(time), event(event) {};
			
			virtual void onUpdate();
			
			virtual ~Timer() {};

	};

}

#endif