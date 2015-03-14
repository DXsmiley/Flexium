#ifndef FLEXIUM_EXTRA_EVENTS
#define FLEXIUM_EXTRA_EVENTS

#include <Flexium/Event.hpp>
#include <Flexium/Object.hpp>

#include <initializer_list>
#include <memory>
#include <vector>

namespace flx {

	class EventPrint: public Event {

		private:

			std::string text;

		public:

			EventPrint(std::string t): Event(), text(t) {};
			virtual void onTrigger();
			virtual ~EventPrint() {};

	};

	class EventCreate : public Event {

		private:

			std::shared_ptr<Object> obj;

		private:

			EventCreate(std::shared_ptr<Object> o): obj(o) {};
			virtual void onTrigger();
			virtual ~EventCreate() {};

	};

	class EventDestroy : public Event {

		private:

			std::shared_ptr<Object> obj;

		public:

			EventDestroy(std::shared_ptr<Object> o): obj(o) {};
			virtual void onTrigger();
			virtual ~EventDestroy() {};

	};

	class EventCompond : public Event {

		private:

			std::vector<std::shared_ptr<Event> > events;

		public:

			EventCompond(std::initializer_list<std::shared_ptr<Event> >);
			// EventCompond(std::initializer_list<Event*>);
			virtual void onTrigger();
			virtual ~EventCompond();

	};

}

#endif