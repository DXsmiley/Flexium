#ifndef FLEXIUM_SPRITE_HPP
#define FLEXIUM_SPRITE_HPP

#include <Flexium/Window.hpp>
#include <Flexium/Transform.hpp>
#include <SFML/Graphics.hpp>

namespace sf {
	class Texture;
}

namespace flx {

	class Vector;

	/**
		Use to load and display images.
	*/
	namespace Sprite {

		void load(const char *, const char *);
		void loadMapping(const char *);

		/**
			Draws a sprite at the given location with alpha value ad specified texture.
		*/
		void draw(double x, double y, double alpha, ::sf::Texture * tex);

		/**
			Draws a sprite at the given location with alpha value.
			Texture is accessed from the texture mapping using the given name.
		*/
		void draw(sf::Transform transform, sf::Color blend, const char * strip_name, int frame);
		void draw(sf::Transform transform, const char * strip_name, int frame);
		void draw(sf::Transform transform, const char * name);
		void draw(double x, double y, double alpha, const char * name);
		void draw(double x, double y, double alpha, std::string name);
		void draw(double x, double y, const char * name);
		void draw(double x, double y, std::string name);
		void draw(Vector pos, const char * name);
		void draw(Vector pos, std::string name);
		void draw(Vector pos, double alpha, const char * name);
		void draw(Vector pos, double alpha, std::string name);
		void draw(double x, double y, double alpha, const char * name, int frame);
		void draw(double x, double y, double alpha, std::string name, int frame);
		void draw(double x, double y, const char * name, int frame);
		void draw(double x, double y, std::string name, int frame);
		void draw(Vector pos, const char * name, int frame);
		void draw(Vector pos, std::string name, int frame);
		void draw(Vector pos, double alpha, const char * name, int frame);
		void draw(Vector pos, double alpha, std::string name, int frame);
		void drawPartial(Vector pos, Vector tex_pos, Vector tex_dim, ::sf::Texture * tex);
		void drawPartial(Vector pos, Vector tex_pos, Vector tex_dim, const char * name);

		int getWidth(const std::string& name);
		int getHeight(const std::string& name);

		::sf::Texture * getTexture(const char *);

	};

}

#endif