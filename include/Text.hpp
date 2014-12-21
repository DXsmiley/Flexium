#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>
#include "Window.hpp"

namespace Text {

	/**
		Load fronts from a mapping file.
	*/
	void loadMapping(const char * filename);

	/**
		Load a font from a file into the cahce and give it a name.
		The name can then be used later to refer to it again.
		@param name - the name of the font used by the program
		@param font - the filename that the font should be loaded from
		@returns nothing
	*/
	void loadFont(const char * name, const char * file);

	/**
		Reutns a pointer to the sf::Font specified by @param name.
		Reutns NULL if no font with that name exists.
	*/
	sf::Font * getFont(const char * name);

	/**
		Draws text using the specified font.
	*/
	void draw(double x, double y, std::string text, const char * font, int size);

	/*
		Draw some text.
	*/
	void draw(Vector pos, std::string text, const char * font, int size);

	/**
		Draw text using the specified font and colour.
	*/
	void draw(double x, double y, std::string text, const char * font, int size, const sf::Color&);

	/*
		Draw some text.
	*/
	void draw(Vector pos, std::string text, const char * font, int size, const sf::Color&);


}

#endif