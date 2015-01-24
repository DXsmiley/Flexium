#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <Flexium/Object.hpp>
#include <Flexium/Flexium.hpp>

// Foaward declaration
namespace sf {
	class Texture;
}

namespace flx {

	class TileMap : public Object {

		private:

			int width;
			int height;
			int * array;
			::sf::Texture * texture; // direct manipulation of sf::Texture for speed
			Vector tile_dim;
			int tex_width;
			int tex_height;

			int index(int x, int y);

		public:

			TileMap(int width, int height);
			//TileMap(unsigned int width, unsigned int height, std::string texture);

			void setTile(int x, int y, int id);
			void setTexture(const char * tex_name);

			virtual void onDraw();
			virtual ~TileMap() {};

	};

}

#endif