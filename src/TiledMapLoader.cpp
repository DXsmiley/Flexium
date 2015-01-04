#include <Flexium/TiledMapLoader.hpp>

#include <Flexium/pugixml.hpp>
#include <Flexium/TileMap.hpp>
#include <Flexium/Console.hpp>
#include <Flexium/World.hpp>

#include <sstream>
#include <locale>

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
		std::cout << "Loading Tiled Map " << filename << std::endl;
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(filename);
		if (!result) {
			std::cout << "An error occured when loading Tiled Map file " << filename << std::endl;
		} else {
			pugi::xml_node root = doc.child("map");
			int tm_width = root.attribute("width").as_int();
			int tm_height = root.attribute("height").as_int();
			//  std::cout << "Width: " << root.attribute("width").as_int(); << std::endl;
			//  std::cout << "Height: " << root.attribute("height").as_int() << std::endl;
			//  std::cout << "Orientation: " << root.attribute("orientation").value() << std::endl;
			// Scan list of tilesets
			const char * tileset_name = "tilemap";
			for (pugi::xml_node node = root.child("tileset"); node; node = node.next_sibling("tileset")) {
				std::cout << "Tileset < " << node.attribute("name").value() << " > " << std::endl;
				tileset_name = node.attribute("name").value();
			}
			// Scan list of tile layers
			for (pugi::xml_node node = root.child("layer"); node; node = node.next_sibling("layer")) {
				std::cout << "Layer < " << node.attribute("name").value() << " > " << std::endl;
				pugi::xml_node data = node.child("data");
				if (std::string("csv") == std::string(data.attribute("encoding").value())) {
					TileMap * tilemap = new TileMap(tm_width, tm_height, tileset_name);
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
					std::cout << "Tile Data format not supported (" << data.attribute("encoding").value() << ")" << std::endl;
				}
			}
			// Scan list of objects
			for (pugi::xml_node node = root.child("objectgroup"); node; node = node.next_sibling("objectgroup")) {
				std::cout << "Object Group < " <<  node.attribute("name").value() << " > " << std::endl;
				std::string group_name = node.attribute("name").value();
				if (rules.count(group_name) > 0) {
					for (pugi::xml_node object : node.children("object")) {
						SpawnInfo info;
						info.world = world;
						info.position = Vector(object.attribute("x").as_int(), object.attribute("y").as_int());
						info.dimensions = Vector(object.attribute("width").as_int(), object.attribute("height").as_int());
						info.name = object.attribute("name").value();
						(*rules[group_name])(info);
					}
				} else {
					Console::Error << "No known action for object group named '" << group_name << "'" << std::endl;
				}
				/*if (group_name == "Walls") {
					for (pugi::xml_node object = node.child("object"); object; object = object.next_sibling("object")) {
						//std::cout << "Creating wall" << std::endl;
						Vector pos(object.attribute("x").as_int(), object.attribute("y").as_int());
						Vector dim(object.attribute("width").as_int(), object.attribute("height").as_int());
						Wall * wall = new Wall();
						wall -> setPosition(pos);
						wall -> setDimensions(dim);
						world -> instanceAdd(wall);
					}
					continue;
				}
				if (group_name == "SpawnGround") {
					for (pugi::xml_node object = node.child("object"); object; object = object.next_sibling("object")) {
						Vector pos(object.attribute("x").as_int(), object.attribute("y").as_int());
						Vector dim(object.attribute("width").as_int(), object.attribute("height").as_int());
						world -> instanceAdd(new SpawnGround(pos, dim));
					}
					continue;
				}*/
			}
			// Scan list of image layers (will probably not be implemented until needed)
		}
	}

}