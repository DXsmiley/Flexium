#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <map>
#include <list>
#include <initializer_list>
#include <memory>

#include <Flexium/Object.hpp>

#include <SFML/System.hpp>

namespace flx {

	/**
		Container that holds and manages all the objects in the game.
	*/
	class World {

		private:

			std::vector<std::shared_ptr<Object> > instances;
			std::vector<std::shared_ptr<Object> > instances_on_instance_added;
			std::vector<std::shared_ptr<Object> > instances_on_update;
			std::vector<std::shared_ptr<Object> > instances_on_draw;
			std::map<size_t, std::list<std::shared_ptr<Object> > > instances_by_typeid;
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
									while (up_to < world -> instances.size() && ((!world -> instances[up_to] -> isAlive()) || (world -> instances[up_to] -> isActive()) || (!std::dynamic_pointer_cast<U>(world -> instances[up_to])))) up_to++;
								} else {
									while (up_to < world -> instances.size() && ((!world -> instances[up_to] -> isAlive()) || (!world -> instances[up_to] -> isActive()) || (!std::dynamic_pointer_cast<U>(world -> instances[up_to])))) up_to++;
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

							std::shared_ptr<U> operator*() {
								return up_to >= world -> instances.size() ? nullptr : std::dynamic_pointer_cast<U>(world -> instances[up_to]);
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
				Returns a list that can be used to iterate over the avaliable objects.
			*/
			template <typename T>
			InstanceList<T> instanceGet() {
				return InstanceList<T>(this, false);
			}

			/**
				Returns a list that can be used to iterate over the avaliable objects.
				@warning This is experemental.
			*/
			template <typename T>
			const std::list<std::shared_ptr<T> >& instanceGetFast() {
				size_t key = typeid(T).hash_code();
				return instances_by_typeid[key];
			}

			/**
				Retuns a list that can be used to iterate over objects that have been deactivated.
			*/
			template <typename T>
			InstanceList<T> instanceGetInactive() {
				return InstanceList<T>(this, true);
			}

			/**
				Returns a single instance of a type of object, or nullptr if none exist.
			*/
			template <typename T>
			std::shared_ptr<T> instanceGetSingle() {
				for (std::shared_ptr<T> i : InstanceList<T>(this, false)) {
					return i;
				}
				return nullptr;
			}

			/**
				Returns a single instance of a type of inactive object, or nullptr if none exist.
			*/
			template <typename T>
			std::shared_ptr<T> instanceGetSingleInactive() {
				for (std::shared_ptr<T> i : InstanceList<T>(this, true)) {
					return i;
				}
				return nullptr;
			}

			/**
				Returns the Nth instance of a type of object.
				This is slow, so use sparingly.
			*/
			template <typename T>
			std::shared_ptr<T> instanceGetSingle(unsigned int n) {
				for (std::shared_ptr<T> i : InstanceList<T>(this, false)) {
					if ((n--) == 0) return i;
				}
				return nullptr;
			}

			/**
				Returns the Nth inactive instance of a type of object.
				This is slow, so use sparingly.
			*/
			template <typename T>
			std::shared_ptr<T> instanceGetSingleInactive(unsigned int n) {
				for (std::shared_ptr<T> i : InstanceList<T>(this, true)) {
					if ((n--) == 0) return i;
				}
				return nullptr;
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
				This appears to do the same thing as instanceGetSingle.
				You should probably ignore this function.
				@warning Ignore this function. I don't know why it's here.
			*/
			template <typename T>
			std::shared_ptr<T> instanceFind(T * o) {
				for (std::shared_ptr<T> i : InstanceList<T>(this, false)) {
					if (i.get() == o) return i;
				}
				return nullptr;
			}

			/**
				Adds an instance of an objects to the world.
				All objects must be added to the world if they are to be processed.
			*/
			std::shared_ptr<Object> instanceAdd(Object * o);

			/**
			*/
			std::shared_ptr<Object> instanceAdd(std::shared_ptr<Object>);


			/**
				Adds multiple instances to the world.
			*/
			void instanceAdd(std::initializer_list<Object *>);
			
			/**
				Processes a single tick.
				Returns true if the program should continue to run, false otherwise.
			*/
			bool simulate();

			/**
				Returns whether the world is set to call Object::onUpdate
			*/
			bool getTriggerUpdate();

			/**
				Returns whether the world is set to call Object::onDraw
			*/
			bool getTriggerDraw();

			/**
				Toggle whether to called the onUpdate function of entities.
				'Meta' instances always have the update function called.
				/sa Object::onUpdate
				/sa Object::setMeta
			*/
			void setTriggerUpdate(bool);
			
			/**
				Toggle whether to called the onDraw function of entities.
				'Meta' instances always have the draw function called.
				/sa Object::onDraw
				/sa Object::setMeta
			*/
			void setTriggerDraw(bool);

	};

}

#endif