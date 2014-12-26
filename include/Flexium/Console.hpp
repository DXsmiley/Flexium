#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <Flexium/Flexium.hpp>
#include <Flexium/Object.hpp>

#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <string>

namespace flx {

    class ConsoleInGame : public Object {

        private:

            bool typing;
            std::string command;
            std::list<std::string> lines;

        public:

            ConsoleInGame(): typing(false), command(), lines() {};

            void addLine(std::string);

            virtual void onCreate();
            virtual void onUpdate();
            virtual void onDraw();
            virtual ~ConsoleInGame() {};

    };

    class ConsoleStream : public std::ostream {

    	private:


            class MyStreamBuffer : public std::stringbuf {

                friend class ConsoleStream;

                protected:

                    std::string prefix;
                    ConsoleInGame * cig;

    			public:

    				MyStreamBuffer(std::string pre): prefix(pre), cig(NULL) {};

    				virtual int sync() {
                        //ConsoleInGame * cig = world -> instanceGetSingle<ConsoleInGame*>();
                        if (cig != NULL) cig -> addLine(prefix + str());
    					std::cout << prefix << str();
    					str("");
    					std::cout.flush();
    					return 0;
    				}

    		} buffer;

    	public:

    		// Construct an std::ostream using the custom buffer, and construct the buffer using our custom prefix
    		ConsoleStream(std::string prefix): std::ostream(&buffer), buffer(prefix) {};

            void setInGameConsole(ConsoleInGame * c);

    };

    namespace Console {

        void commandSet(std::string, void (*)(std::vector<std::string>));

    	extern ConsoleStream Log;
    	extern ConsoleStream Warn;
    	extern ConsoleStream Error;

    };

}

#endif