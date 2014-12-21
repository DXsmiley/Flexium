#ifndef TIMER_HPP
#define TIMER_HPP

#include "Object.hpp"

class Event;

class Timer: public Object {

	private:

		unsigned int mytime;
		Event * event;

	public:

		Timer(unsigned int t, Event * e): mytime(t), event(e) {};
		virtual void onUpdate();
		virtual ~Timer() {};

};

#endif