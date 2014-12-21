#ifndef FLEXIUM_H
#define FLEXIUM_H

#include <exception>
#include <string>

#include "Vector.hpp"

// foaward declaration
namespace sf {
	class Color;
}

/**
	Exception class that is thrown by Flexium when something goes wrong.
*/
class FlexiumException: public std::exception {

	private:

		std::string text;

	public:

		FlexiumException(const char * t): text(t) {};
		FlexiumException(std::string t): text(t) {};

		virtual const char * what() const throw() {
			return text.c_str();
		}

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

#endif