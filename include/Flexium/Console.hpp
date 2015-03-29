#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <Flexium/ConsoleMinimal.hpp>
#include <Flexium/Flexium.hpp>
#include <Flexium/Object.hpp>

#include <iostream>
#include <list>
#include <vector>
#include <string>

namespace flx {

	class World;

	/**
		Debugging tool.
		To use it, simply add an instance of it to the world.
	*/
	class ConsoleInGame : public Object {

		private:

			bool typing;
			std::string command;
			std::list<std::string> lines;

		public:

			ConsoleInGame(): typing(false), command(), lines() {};

			void addLine(std::string);
			void clear();
			
			virtual void onCreate();
			virtual void onUpdate();
			virtual void onDraw();
			virtual ~ConsoleInGame() {};

	};

	namespace Console {

		/**
			Used to specify a console command.
		*/
		struct CommandInfo {
			std::vector<std::string> args;
			World * world;
			ConsoleInGame * console;
		};

		/**
			Used to add a comment to the in-game console.
		*/
		void commandSet(std::string, void (*)(const CommandInfo&));

	}

}

#endif