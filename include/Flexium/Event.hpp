#ifndef EVENT_HPP
#define EVENT_HPP

namespace flx {

	class World;

	/**
		Events are things that occur.
		@warning They should be handled using std::shared_ptr
	*/
	class Event {

		protected:

			World * world;

		public:

			/**
				Create a new event with no associated world. Not recommended.
			*/
			Event(): world(nullptr) {};

			/*
				Create a new event a specify a world that it belongs to.
			*/
			Event(World * w): world(w) {};
			
			/*
				Get the world that the event is associated with.
				\returns The world.
			*/
			World * getWorld();

			/*
				Assign the event to a world.
			*/
			void setWorld(World *);
			
			/*
				Reassign the event and trigger it.
			*/
			void trigger(World * w);
			
			/*
				Reassign the event and trigger it.
			*/
			void onTrigger(World * w);

			/*
				Trigger the event.
				\warning Overriding this is for backwards compatibility only.
			*/
			virtual void trigger();

			/*
				Trigger the event.
				This should be overridden when defining your own events.
			*/
			virtual void onTrigger() {};

			/**
				Destroy the event.
				May have to be overridden by when defining your own event.
			*/
			virtual ~Event() {};

	};

}

#endif