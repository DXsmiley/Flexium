#ifndef EVENT_HPP
#define EVENT_HPP

class World;

class Event {

	protected:

		World * world;

	public:

		Event(): world(0) {};
		Event(World * w): world(w) {};
		World * getWorld();
		void setWorld(World *);
		virtual void trigger() = 0;
		virtual ~Event() {};

};

#endif