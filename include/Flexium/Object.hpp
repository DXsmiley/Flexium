#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <Flexium/Flexium.hpp>
#include <Flexium/Memory.hpp>

namespace flx {

	class World;

	class Object {

		private:

			int depth;
			bool alive;
			bool active;
			bool persistent;
			bool meta;
			unsigned int id; // Should be made 'readonly' sometime in the future
			World * my_world;

		protected:

			Vector position;
			Vector position_previous;
			Vector dimensions;
			Vector origin;

		public:

			/**
				Construct a new object.
				Upon construction, objects adhere to the following conditions:
				 - isAlive() will return true.
				 - getID() will return an (incorrect) id of 0.
				 - getWorld() will return a null pointer
			*/
			Object(): depth(0), alive(true), active(true), persistent(false), meta(false), id(0), my_world(nullptr) {};

			// control and meta queries

			/**
				Returns if the object is currently alive or not.
				Objects are considered to be alive upon construction.
				World::simulate() will only call onUpdate() or onDraw() on objects that are alive and active.
			*/
			bool isAlive() const;

			/**
				Returns is the object is currently active.
				World::simulate() will only call onUpdate() or onDraw() on objects that are alive and active.
			*/
			bool isActive() const;

			/**
				Activates the object.
				Will have no effect if the object is already active.
				@see isActive
			*/
			void activate();

			/**
				Deactivates the object.
				Will have no effect if the object is already inactive.
				@see isActive
			*/
			void deactivate();

			/**
				Returns wheater the object is persistent.
			*/
			bool isPersistent() const;

			/**
				Sets the object's persistence bit.
			*/
			void setPersistent(bool);

			/**
				Returns the depth of the object.
				Depth determines the order in which objects are processed during the World::simulate() update and draw loops.
				Depth also determines the order in which objects are returned by World::instanceGet()
				@see setDepth
			*/
			int getDepth() const;

			/**
				Sets the depth of the object.
				See getDepth for more unformation of depth.
			*/
			void setDepth(int);

			/**
				Returns wheather the object is 'meta'. Meta objects still have their events triggered even if the world is paused.
				Thi is usefull for begugging objects.
			*/
			bool isMeta();

			/**
				Set the meta status of the object.
			*/
			void setMeta(bool);

			/**
				Returns the numerical ID of the object.
				Objects are assigned ID's in increasing order by the world that they are associated with.
			*/
			int getID() const;

			/**
				Returns the world the object is associated with.
				An object cannot be associated with more than one world at a time.
			*/
			World * getWorld() const;

			/**
				System function that is strictly NOT to be called by the user.
				This function is called when an object is associated with a world through World::instanceAdd().
				If this function is called more than once on any object, it will throw an error.
			*/
			void registerWorld(int, World *);

			/**
				Destroys the object. This means that the object is not longer alive.
				This invokes the virtual method onDestroy();
				This is to be used, not delete, as the World still needs to perform some cleanup actions even after the object is 'dead'.
				Dead objects will not have their onUpdate() or onDraw() functions invoked, nor will World::instanceGet() return it.
			*/
			void destroy();

			/**
				Function that is called on the object when the object is added to the world.
				This functin should only be called by the system, not by the user.
				This function has the folling preconditions:
				 - The object is alive.
				 - The object is associated with a world.
				 - The object has a valid id.
			*/
			virtual void onCreate() {};

			/**
				The update function is called once on every object every game tick.
				This is not called on objects that do not implement it.
			*/
			virtual void onUpdate();

			/**
				The draw function is called once every object every frame.
				This may or may not be called at the same rate as onUpdate().
				This is not called on objects that do not implement it.
			*/
			virtual void onDraw();

			/**
				Called when the object is destroyed.
				Prior to the function being invoked, the object is considered dead.
				@see destroy()
			*/
			virtual void onDestroy() {};

			/**
				Called when another object is added to the world.
				This is not called on objects that do not implement it.
			*/
			virtual void onInstanceAdded(std::shared_ptr<Object>);

			/**
				Virtual destructor on object.
				Must be overridden by all subclasses, otherwise undefined behaviour occurs.
			*/
			virtual ~Object() {};

			/**
				Sets the position of the object within the world.
			*/
			void setPosition(double x, double y);
			
			/**
				Sets the position of the object within the world.
			*/
			void setPosition(Vector position);
			
			/**
				Returns the object's current position.
			*/
			Vector getPosition();

			/**
				Sets the object's width and height.
			*/
			void setDimensions(double width, double height);
		
			/**
				Sets the object's width and height.
			*/
			void setDimensions(Vector dimensions);

			/**
				Returns the current dimensions of the object.
				For the purpose of simplicity, all objects are considered to be rectangular, as any shape can be encoumpassed by a rectangular bounding box.
			*/
			Vector& getDimensions();

			/**
				Centres the object's centre.
				@see setOrigin
			*/
			void setOriginCentre();

			/**
				Sets the object's origin.
				The object's object is the point from which it's bounds are calculated.
				For example, if the origin is (0, 0), then the object's x and y position will represent its top-left corner.
				If the origin is(1, 1), the the object's x and y values will represent its bottom-right corner.
			*/
			void setOrigin(double x, double y);

			/**
				Sets the object's origin;
			*/
			void setOrigin(Vector v);

			/**
				Returns the difference between the object's x position and it's leftmost bound.
			*/
			double marginLeft();
			
			/**
				Returns the difference between the object's x position and it's rightmost bound.
			*/
			double marginRight();
			
			/**
				Returns the difference between the object's y position and it's topmost bound.
			*/
			double marginTop();
			
			/**
				Returns the difference between the object's y position and it's bottommost bound.
			*/
			double marginBottom();
			
			/**
				Retuns the object's leftmost (smallest) x position.
			*/
			double boundLeft();
			
			/**
				Retuns the object's rightmost (largest) x position.
			*/
			double boundRight();
			
			/**
				Retuns the object's topmost (smallest) y position.
			*/
			double boundTop();
			
			/**
				Retuns the object's bottommost (largest) y position.
			*/
			double boundBottom();

			/**
				Returns the coordinated of the top left of the object.
			*/
			Vector boundTopLeft();

			/**
				Returns the coordinated of the top right of the object.
			*/
			Vector boundTopRight();
			
			/**
				Returns the coordinated of the bottom left of the object.
			*/
			Vector boundBottomLeft();
			
			/**
				Returns the coordinated of the bottom right of the object.
			*/
			Vector boundBottomRight();

			/**
				Sets the width and height of the object to the width and height of a sprite.
			*/
			void setDimensionsToSprite(const char *);

			/**
				Sets the width and height of the object to the width and height of a sprite.
			*/
			void setDimensionsToSprite(std::string);

			/**
				Checks if the current object collides with another based on their relative positions and bounding boxes.
			*/
			bool collidesWith(flx::shared_ptr_autocast<Object>);

			/**
				Checks if the point is contained within the boinding box of the object.
			*/
			bool collidesWith(flx::Vector);

	};

}

#endif