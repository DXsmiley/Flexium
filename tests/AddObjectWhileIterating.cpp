/*

	This code adds an object while the list objects are being iterated over.
	It shows that (at the time of writing) this last object does not get iterated over.

*/

#include <Flexium/ConsoleMinimal.hpp>
#include <Flexium/World.hpp>
#include <Flexium/Object.hpp>

using namespace flx;

class ObjectOne : public Object {

	protected:

		std::string name;

	public:

		ObjectOne(std::string s): name(s) {};

		virtual void sayName() {
			Console::Log << name << std::endl;
		}

		virtual ~ObjectOne() {};

};

class ObjectTwo : public ObjectOne {

	public:

		ObjectTwo(std::string s): ObjectOne(s) {};

		virtual void sayName() {
			Console::Log << name << std::endl;
			// Do something sneaky!
			getWorld() -> instanceAdd(new ObjectOne("Ben"));
		}

		virtual ~ObjectTwo() {};

};

int main() {
	World world;
	world.instanceAdd(new ObjectOne("Bob"));
	world.instanceAdd(new ObjectTwo("Bill"));
	for (auto i : world.instanceGet<ObjectOne*>()) {
		i -> sayName();
	}
}