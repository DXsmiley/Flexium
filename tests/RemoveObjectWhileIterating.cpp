/*

	This shows that objects that are destroyed before they are iterated over are never iterated over.

*/

#include <iostream>
#include <fstream>

#include <Flexium/World.hpp>
#include <Flexium/Object.hpp>

using namespace flx;

class ObjectOne : public Object {

	protected:

		std::string name;

	public:

		ObjectOne(std::string s): name(s) {};

		virtual void sayName() {
			std::cout << name << std::endl;
		}

		virtual ~ObjectOne() {};

};

class ObjectTwo : public ObjectOne {

	private:

		Object * target;

	public:

		ObjectTwo(std::string s, Object * o): ObjectOne(s), target(o) {};

		virtual void sayName() {
			std::cout << name << std::endl;
			// Do something sneaky!
			target -> destroy();
		}

		virtual ~ObjectTwo() {};

};

int main() {
	World world;
	Object * target = new ObjectOne("Bob");
	world.instanceAdd(new ObjectTwo("Bill", target));
	world.instanceAdd(target);
	for (auto i : world.instanceGet<ObjectOne*>()) {
		i -> sayName();
	}
}