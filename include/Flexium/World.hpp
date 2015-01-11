#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <initializer_list>

#include <Flexium/Object.hpp>

namespace flx {

	/**
		Container that holds and manages all the objects in the game.
	*/
	class World {

		private:

			std::vector<Object *> instances;
			unsigned int id_counter;
			bool trigger_update;
			bool trigger_draw;

		public:

			template <typename T>
			class InstanceList {

				private:

					World * world;
					bool inactive;

					template <typename U>
					class InstanceIterator {

						private:

							World * world;
							unsigned int up_to;
							bool inactive;

							void next() {
								if (inactive) {
									while (up_to < world -> instances.size() && ((!world -> instances[up_to] -> isAlive()) || (world -> instances[up_to] -> isActive()) || (dynamic_cast<U>(world -> instances[up_to]) == NULL))) up_to++;
								} else {
									while (up_to < world -> instances.size() && ((!world -> instances[up_to] -> isAlive()) || (!world -> instances[up_to] -> isActive()) || (dynamic_cast<U>(world -> instances[up_to]) == NULL))) up_to++;
								}
							}

						public:

							InstanceIterator(World * w, unsigned int place, bool ina) {
								world = w;
								up_to = place;
								inactive = ina;
								next();
							}
							
							bool operator!=(const InstanceIterator& other) {
								return world != other.world || up_to != other.up_to;
							}

							const InstanceIterator& operator++() {
								up_to++;
								next();
								return *this;
							}

							U operator*() {
								return up_to >= world -> instances.size() ? NULL : dynamic_cast<U>(world -> instances[up_to]);
							}

					};

				public:

					InstanceList(World * w, bool in) {
						world = w;
						inactive = in;
					}

					InstanceIterator<T> begin() {
						return InstanceIterator<T>(world, 0, inactive);
					}

					InstanceIterator<T> end() {
						return InstanceIterator<T>(world, world -> instances.size(), inactive);
					}

					/**
						Counts the number of objects in the list.
						This is actually slow, do please cache your results.
					*/
					unsigned int size() {
						unsigned int count = 0;
						for (InstanceIterator<T> i = begin(); i != end(); ++i) {
							count++;
						}
						return count;
					}

			};

			/**
				Woo. A constructor.
			*/
			World();

			/**
				Retuns a list that can be used to iterate over the avaliable objects.
			*/
			template <typename T>
			InstanceList<T> instanceGet() {
				return InstanceList<T>(this, false);
			}

			/**
				Retuns a list that can be used to iterate over objects that have been deactivated.
			*/
			template <typename T>
			InstanceList<T> instanceGetInactive() {
				return InstanceList<T>(this, true);
			}

			/**
				Returns a single instance of a type of object, or NULL if none exist.
			*/
			template <typename T>
			T instanceGetSingle() {
				for (T i : InstanceList<T>(this, false)) {
					return i;
				}
				return NULL;
			}

			/**
				Returns a single instance of a type of inactive object, or NULL if none exist.
			*/
			template <typename T>
			T instanceGetSingleInactive() {
				for (T i : InstanceList<T>(this, true)) {
					return i;
				}
				return NULL;
			}

			/**
				Returns the Nth instance of a type of object.
				This is slow, so use sparingly.
			*/
			template <typename T>
			T instanceGetSingle(unsigned int n) {
				for (T i : InstanceList<T>(this, false)) {
					if ((n--) == 0) return i;
				}
				return NULL;
			}

			/**
				Returns the Nth inactive instance of a type of object.
				This is slow, so use sparingly.
			*/
			template <typename T>
			T instanceGetSingleInactive(unsigned int n) {
				for (T i : InstanceList<T>(this, true)) {
					if ((n--) == 0) return i;
				}
				return NULL;
			}

			/**
				Counts the number of instances of a type of object.
				This is slow, so don't overuse it.
			*/
			template <typename T>
			unsigned int instanceCount() {
				return InstanceList<T>(this, false).size();
			}

			/**
				Counts the number of instances of a type of object.
				This is slow, so don't overuse it.
			*/
			template <typename T>
			unsigned int instanceCountInactive() {
				return InstanceList<T>(this, true).size();
			}

			/**
				Adds an instance of an objects to the world.
				All objects must be added to the world if they are to be processed.
			*/
			Object * instanceAdd(Object * o);

			/**
				Adds multiple instances to the world.
			*/
			void instanceAdd(std::initializer_list<Object *>);
			
			/**
				Processes a single tick.
				Returns true if the programm should continue to run, false otherwise.
			*/
			bool simulate();

			bool getTriggerUpdate();
			bool getTriggerDraw();
			void setTriggerUpdate(bool);
			void setTriggerDraw(bool);

	};

}

#endif