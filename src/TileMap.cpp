#include "TileMap.hpp"
#include "Sprite.hpp"

TileMap::TileMap(int w, int h, const char * t) {
	width = w;
	height = h;
	texture = Sprite::getTexture(t);
	array = new int[width * height];
	tile_dim = Vector(16, 16); // not flexible D:
	sf::Vector2u ts = texture -> getSize();
	tex_width = ts.x / tile_dim.x;
	tex_height = ts.y / tile_dim.y;
}

int TileMap::index(int x, int y) {
	return x + (y * width);
}

void TileMap::setTile(int x, int y, int tid) {
	array[index(x, y)] = tid;
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