#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Object.hpp"
#include "Flexium.hpp"

#include <SFML/Graphics.hpp>

class TileMap : public Object {

	private:

		int width;
		int height;
		int * array;
		sf::Texture * texture;
		Vector tile_dim;
		int tex_width;
		int tex_height;

		int index(int x, int y);

	public:

		TileMap(int width, int height, const char * texture);
		//TileMap(unsigned int width, unsigned int height, std::string texture);

		void setTile(int x, int y, int id);

		virtual void onDraw();
		virtual ~TileMap() {};

};

#endif