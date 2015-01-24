#include <Flexium/TileMap.hpp>
#include <Flexium/Sprite.hpp>
#include <Flexium/Console.hpp>

#include <SFML/Graphics.hpp>

namespace flx {

	TileMap::TileMap(int w, int h) {
		width = w;
		height = h;
		array = new int[width * height];
	}

	int TileMap::index(int x, int y) {
		return x + (y * width);
	}

	void TileMap::setTile(int x, int y, int tid) {
		array[index(x, y)] = tid;
	}

	void TileMap::setTexture(const char * tex_name) {
		if (tex_name == NULL) {
			Console::Error << "Attempted to set TileMap texture to NULL texture" << std::endl;
		} else {
			texture = Sprite::getTexture(tex_name);
			tile_dim = Vector(16, 16); // not flexible D:
			::sf::Vector2u ts = texture -> getSize();
			tex_width = ts.x / tile_dim.x;
			tex_height = ts.y / tile_dim.y;
		}
	}

	void TileMap::onDraw() {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				int t = array[index(x, y)];
				if (t >= 0) {
					Vector tex_pos((t % tex_width) * tile_dim.x, (t / tex_width) * tile_dim.y);
					Vector pos(x * tile_dim.x, y * tile_dim.y);
					Sprite::drawPartial(pos, tex_pos, tile_dim, texture);
				}
			}
		}
	}

}