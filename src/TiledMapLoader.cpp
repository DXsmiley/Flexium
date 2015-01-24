#include <Flexium/TiledMapLoader.hpp>

#include <Flexium/pugixml.hpp>
#include <Flexium/TileMap.hpp>
#include <Flexium/Console.hpp>
#include <Flexium/World.hpp>
#include <Flexium/Window.hpp>

#include <SFML/Graphics.hpp>

#include <sstream>
#include <locale>

static int hexDigitToInt(char c) {
	return c >= 'a' ? c - 'a' + 10 : c >= 'A' ? c - 'A' + 10 : c - '0';
}

namespace flx {

	// Modified code from Stack Overflow: http://stackoverflow.com/a/1895584/2002307
	struct CSVLocale: std::ctype<char> {

		CSVLocale(): std::ctype<char>(get_table()) {};

		static std::ctype_base::mask const* get_table() {
			static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());
			rc[','] = std::ctype_base::space;
			rc['\n'] = std::ctype_base::space;
			rc[' '] = std::ctype_base::space;
			return &rc[0];
		}
	};

	RuleSet rules;

	RuleSet& tiledMapRules() {
		return rules;
	}

	void tiledMapLoad(const char * filename, World * world) {
		Console::Log << "Loading Tiled Map " << filename << std::endl;
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(filename);
		if (!result) {
			Console::Error << "  An error occured while parsing Tiled Map file " << filename << std::endl;
		} else {
			pugi::xml_node root = doc.child("map");
			if (root.attribute("backgroundcolor")) {
				std::string s = root.attribute("backgroundcolor").value();
				int b = (hexDigitToInt(s[5]) * 16) + hexDigitToInt(s[6]);
				int g = (hexDigitToInt(s[3]) * 16) + hexDigitToInt(s[4]);
				int r = (hexDigitToInt(s[1]) * 16) + hexDigitToInt(s[2]);
				// std::cout << "Background color: " << s << ' ' << r << ' ' << g << ' ' << b << std::endl;
				Window::setClearColor(::sf::Color(r, g, b));
			}
			int tm_width = root.attribute("width").as_int();
			int tm_height = root.attribute("height").as_int();

			// Scan list of tilesets
			struct tileset_t {
				std::string name;
				int tid;
				int tile_width;
				int tile_height;
			};
			std::list<tileset_t> tilesets;
			for (pugi::xml_node node_tilemap : root.children("tileset")) {
				Console::Log << "  Tileset < " << node_tilemap.attribute("name").value() << " > " << std::endl;
				// tileset_name = node_tilemap.attribute("name").value();
				tileset_t ts;
				ts.name = node_tilemap.attribute("name").value();
				ts.tid = node_tilemap.attribute("firstgid").as_int(1);
				ts.tile_width = node_tilemap.attribute("tilewidth").as_int();
				ts.tile_height = node_tilemap.attribute("tileheight").as_int();
				tilesets.push_back(ts);
			}

			// Scan list of tile layers
			for (pugi::xml_node node_tile_layer : root.children("layer")) {
				Console::Log << "  Layer < " << node_tile_layer.attribute("name").value() << " > " << std::endl;
				pugi::xml_node data = node_tile_layer.child("data");
				if (std::string("csv") == std::string(data.attribute("encoding").value())) {
					TileMap * tilemap = new TileMap(tm_width, tm_height);
					tilemap -> setTexture(tilesets.front().name.c_str());
					std::stringstream ss;
					ss.imbue(std::locale(std::locale(), new CSVLocale())); // Give the stringstream the locale
					ss.str(std::string(data.child_value()));
					for (int y = 0; y < tm_height; y++) {
						for (int x = 0; x < tm_width; x++) {
							int tile_id = 0;
							ss >> tile_id;
							tilemap -> setTile(x, y, tile_id - 1);
						}
					}
					world -> instanceAdd(tilemap);
				} else {
					Console::Error << "  Tile Data format not supported (" << data.attribute("encoding").value() << ")" << std::endl;
				}
			}

			// Scan list of objects
			for (pugi::xml_node node : root.children("objectgroup")) {
				std::cout << "Object Group < " <<  node.attribute("name").value() << " > " << std::endl;
				std::string group_name = node.attribute("name").value();
				if (rules.count(group_name) > 0) {
					for (pugi::xml_node object : node.children("object")) {
						SpawnInfo info;
						info.world = world;
						info.position = Vector(object.attribute("x").as_int(), object.attribute("y").as_int());
						info.dimensions = Vector(object.attribute("width").as_int(), object.attribute("height").as_int());
						info.name = object.attribute("name").value();
						for (pugi::xml_node param_node : object.child("properties").children("property")) {
							info.parameters[param_node.attribute("name").value()] = param_node.attribute("value").value();
							// std::cout << "Loaded paremeter " << param_node.attribute("name").value() << " : " << param_node.attribute("value").value() << std::endl;
						}
						(*rules[group_name])(info);
					}
				} else {
					Console::Error << "No known action for object group named '" << group_name << "'" << std::endl;
				}
			}
			// Scan list of image layers (will probably not be implemented until much later)
		}
	}

}