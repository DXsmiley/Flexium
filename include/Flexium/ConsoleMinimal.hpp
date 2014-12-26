#ifndef FLEXIUM_CONSOLE_MINIMAL_HPP
#define FLEXIUM_CONSOLE_MINIMAL_HPP

#include <iostream>
#include <string>
#include <sstream>

namespace flx {

	class ConsoleInGame;

	class ConsoleStream : public std::ostream {

		private:


			class MyStreamBuffer : public std::stringbuf {

				friend class ConsoleStream;

				protected:

					std::string prefix;
					ConsoleInGame * cig;

				public:

					MyStreamBuffer(std::string pre): prefix(pre), cig(NULL) {};
					virtual int sync();

			} buffer;

		public:

			// Construct an std::ostream using the custom buffer, and construct the buffer using our custom prefix
			ConsoleStream(std::string prefix): std::ostream(&buffer), buffer(prefix) {};

			void setInGameConsole(ConsoleInGame * c);

	};

	namespace Console {

		extern ConsoleStream Log;
		extern ConsoleStream Warn;
		extern ConsoleStream Error;

	};

}

#endif