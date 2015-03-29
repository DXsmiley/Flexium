#ifndef FLEXIUM_CONSOLE_MINIMAL_HPP
#define FLEXIUM_CONSOLE_MINIMAL_HPP

#include <iostream>
#include <string>
#include <sstream>

namespace flx {

	class ConsoleInGame;

	/**
		Version of std::ostream that is used to capture output.
	*/
	class ConsoleStream : public std::ostream {

		private:

			class MyStreamBuffer : public std::stringbuf {

				friend class ConsoleStream;

				protected:

					std::string prefix;
					ConsoleInGame * cig;

				public:

					MyStreamBuffer(std::string pre): prefix(pre), cig(nullptr) {};
					virtual int sync();

			} buffer;

		public:

			// Construct an std::ostream using the custom buffer, and construct the buffer using our custom prefix
			ConsoleStream(std::string prefix): std::ostream(&buffer), buffer(prefix) {};

			void setInGameConsole(ConsoleInGame * c);

	};

	namespace Console {

		/**
			Used to print most output.
			This is recommended over standard streams as it is compatiable with flx::ConsoleInGame.
		*/
		extern ConsoleStream Log;

		/**
			Used to print warning errors.
			This is recommended over standard streams as it is compatiable with flx::ConsoleInGame.
		*/
		extern ConsoleStream Warn;
		
		/**
			Used to print warning errors.
			This is recommended over standard streams as it is compatiable with flx::ConsoleInGame.
		*/
		extern ConsoleStream Error;

	};

}

#endif