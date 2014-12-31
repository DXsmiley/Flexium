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

		struct CommandInfo {
			std::vector<std::string> args;
			World * world;
			ConsoleInGame * console;
		};

		void commandSet(std::string, void (*)(const CommandInfo&));

	}

}

#endif