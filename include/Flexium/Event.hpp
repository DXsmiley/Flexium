#ifndef EVENT_HPP
#define EVENT_HPP

namespace flx {

	class World;

	/**
		Events are things that occur...
		@warning Stuff happens.
	*/
	class Event {

		protected:

			World * world;

		public:

			Event(): world(0) {};
			Event(World * w): world(w) {};
			World * getWorld();
			void setWorld(World *);
			virtual void trigger();
			virtual void onTrigger() {};
			virtual ~Event() {};

	};

}

#endif