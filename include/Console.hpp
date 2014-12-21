#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "Flexium.hpp"
#include "Object.hpp"
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <string>

/*

Example cutom stream taken from http://stackoverflow.com/questions/2212776/overload-handling-of-stdendl

class MyStream: public std::ostream
{
    // Write a stream buffer that prefixes each line with Plop
    class MyStreamBuf: public std::stringbuf
    {
        std::ostream&   output;
        public:
            MyStreamBuf(std::ostream& str)
                :output(str)
            {}

        // When we sync the stream with the output. 
        // 1) Output Plop then the buffer
        // 2) Reset the buffer
        // 3) flush the actual output stream we are using.
        virtual int sync ( )
        {
            output << "[blah]" << str();
            str("");
            output.flush();
            return 0;
        }
    };

    // My Stream just uses a version of my special buffer
    MyStreamBuf buffer;
    public:
        MyStream(std::ostream& str)
            :std::ostream(&buffer)
            ,buffer(str)
        {
        }
};


int main()
{
    MyStream myStream(std::cout);
    myStream << 1 << 2 << 3 << std::endl << 5 << 6 << std::endl << 7 << 8 << std::endl;
} 

*/

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

#endif