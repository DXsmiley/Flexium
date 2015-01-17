/*
	This file kinda needs to be removed. It makes so sense as it is at the moment.
	The Exception should probably be moved to utility, or debug (along with the in-game console and the debug variable).
	graphicDrawRectangleOutline should be either removed or added to some kind of graphical module.
*/

#ifndef FLEXIUM_H
#define FLEXIUM_H

#include <exception>
#include <string>

#include <Flexium/Vector.hpp>

// foaward declaration
namespace sf {
	class Color;
}

namespace flx {

	/**
		Exception class that is thrown by Flexium when something goes wrong.
	*/
	class FlexiumException : public std::exception {

		protected:

			std::string text;

		public:

			FlexiumException(const char * t): text(t) {};
			FlexiumException(std::string t): text(t) {};

			virtual const char * what() const throw() {
				return text.c_str();
			}

	};

	class FlexiumExceptionNotImplemented : public FlexiumException {

		public:

			FlexiumExceptionNotImplemented(const char * t): FlexiumException(t) {};
			FlexiumExceptionNotImplemented(std::string t): FlexiumException(t) {};

	};

	void graphicDrawRectangleOutline(Vector pos, Vector dim);
	void graphicDrawRectangleOutline(Vector pos, Vector dim, sf::Color);

	/*struct Vector {
		double x, y;
		Vector(): x(0), y(0) {};
		Vector(double a, double b): x(a), y(b) {};
		Vector operator +(const Vector& v) const {
			return Vector(x + v.x, y + v.y);
		}
	};*/

	extern bool debug;

}

#endif