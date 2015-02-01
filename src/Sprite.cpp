#include <Flexium/Sprite.hpp>
#include <Flexium/Window.hpp>
#include <Flexium/Flexium.hpp>
#include <Flexium/Console.hpp>

#include <map>
#include <SFML/Graphics.hpp>

#include <Flexium/pugixml.hpp>

namespace flx {

	namespace Sprite {

		//std::map<std::string, ::sf::Texture *> textures;

		struct sprite_struct {

			::sf::Texture * texture;
			int x;
			int y;
			int width;
			int height;
			int origin_x;
			int origin_y;
			int n_frames;
			int oversized;
			int undersized;

		};

		std::map<std::string, sprite_struct> sprite_mapping;

		void load(const char * name, const char * file) {
			::sf::Texture * t = new ::sf::Texture;
			if (!t -> loadFromFile(file)) {
				throw FlexiumException(std::string("Failed to load image file: ") + std::string(file));
			}
			sprite_struct spr;
			spr.texture = t;
			spr.x = 0;
			spr.y = 0;
			spr.width = t -> getSize().x;
			spr.height = t -> getSize().y;
			spr.n_frames = 1;
			spr.oversized = 1;
			sprite_mapping[std::string(name)] = spr;
		}

		::sf::Texture * loadTexture(const char * filename) {
			::sf::Texture * tex_object = new ::sf::Texture;
			if (!tex_object -> loadFromFile(filename)) {
				throw FlexiumException(std::string("Failed to load image file: ") + std::string(filename));
			}
			return tex_object;
		}

		// load sprite data from a spritesheet
		void loadMapping(const char * filename) {
			Console::Log << "Loading sprite sheet from " << filename << std::endl;
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_file(filename);
			if (!result) {
				Console::Error << "An error occured while parsing sprite sheet XML!" << std::endl;
				Console::Error << result.description() << " : " << result.offset << std::endl;

			} else {
				pugi::xml_node root = doc.child("spritesheet");
				if (root.attribute("format").as_int() == 2) {
					// new format that supports animation strips
					for (pugi::xml_node tex_node : root.children("texture")) {
						// load the texture
						std::string tex_file = tex_node.attribute("source").value();
						::sf::Texture * tex_object = loadTexture(tex_file.c_str());
						int oversized = tex_node.attribute("oversized").as_int(1);
						// read in strip mappings
						for (pugi::xml_node strip_node : tex_node.children("strip")) {
							std::string strip_name = strip_node.attribute("name").value();
							if (sprite_mapping.count(strip_name) > 0) {
								Console::Warn << "Multiple sprite strips with same name '" << strip_name << "'" << std::endl;
							}
							sprite_struct spr;
							spr.texture = tex_object;
							spr.x = strip_node.attribute("x").as_int(0);
							spr.y = strip_node.attribute("y").as_int(0);
							spr.width = strip_node.attribute("width").as_int(tex_object -> getSize().x);
							spr.height = strip_node.attribute("height").as_int(tex_object -> getSize().y);
							spr.n_frames = strip_node.attribute("frames").as_int(1);
							spr.origin_x = strip_node.attribute("origin_x").as_int(0);
							spr.origin_y = strip_node.attribute("origin_y").as_int(0);
							spr.oversized = oversized;
							// Console::Log << "Strip: " << strip_name << ", " << spr.x << ", " << spr.y << std::endl;
							sprite_mapping[strip_name] = spr;
						}
					}
				}
				// old format that was never fully functional (static images only)
				for (pugi::xml_node spr_node : root.children("sprite")) {
					std::string spr_name = spr_node.attribute("name").value();
					for (pugi::xml_node frame_node : spr_node.children("frame")) {
						std::string fr_source = frame_node.attribute("source").value();
						load(spr_name.c_str(), fr_source.c_str());
					}
				}
			}
		}

		void draw(sf::Transform transform, sf::Color blend, const char * strip_name, int frame) {
			if (sprite_mapping.count(std::string(strip_name)) == 1) {
				sprite_struct& ss = sprite_mapping[strip_name];
				while (frame < 0) frame += ss.n_frames; // maybe this should just be assert()ed and throw an error if it fails? unsigned int?
				frame %= ss.n_frames;
				::sf::Sprite spr(*ss.texture);
				spr.setColor(blend);
				spr.setTextureRect(::sf::IntRect(ss.x + (ss.width * frame), ss.y, ss.width, ss.height));
				sf::Transform sys_transform;
				float scale = 1.0 / (float)ss.oversized;
				sys_transform.scale(scale, scale);
				sys_transform.translate(0 - ss.origin_x, 0 - ss.origin_y);
				Window::getHandle() -> draw(spr, transform * sys_transform);
			} else {
				Console::Error << "No sprite strip named '" << strip_name << "'" << std::endl;
			}
		}

		void draw(sf::Transform trans, const char * strip_name, int frame) {
			draw(trans, sf::Color::White, strip_name, frame);
		}

		void draw(sf::Transform trans, const char * name) {
			draw(trans, sf::Color::White, name, 1);
		}

		void draw(double x, double y, double alpha, const char * strip_name, int frame) {
			sf::Transform trans;
			trans.translate(x, y);
			draw(trans, ::sf::Color(255, 255, 255, std::min(255.0, alpha * 255)), strip_name, frame);
		}

		void draw(double x, double y, double alpha, ::sf::Texture * tex) {
			//assertStarted();
			::sf::Sprite spr(*tex);
			spr.setPosition(x, y);
			spr.setColor(::sf::Color(255, 255, 255, std::min(255.0, alpha * 255)));
			Window::getHandle() -> draw(spr);
		}

		// without frame
		void draw(double x, double y, double alpha, const char * name) {
			draw(x, y, 1, name, 0);
		}

		void draw(double x, double y, const char * name) {
			draw(x, y, 1, name, 0);
		}

		void draw(double x, double y, std::string name) {
			draw(x, y, 1, name.c_str(), 0);
		}

		void draw(Vector pos, std::string name) {
			draw(pos.x, pos.y, 1, name.c_str(), 0);
		}

		void draw(Vector pos, const char * name) {
			draw(pos.x, pos.y, 1, name, 0);
		}

		void draw(Vector pos, double alpha, std::string name) {
			draw(pos.x, pos.y, alpha, name.c_str(), 0);
		}

		void draw(Vector pos, double alpha, const char * name) {
			draw(pos.x, pos.y, alpha, name, 0);
		}

		// with frame
		void draw(double x, double y, const char * name, int frame) {
			draw(x, y, 1, name, frame);
		}

		void draw(double x, double y, std::string name, int frame) {
			draw(x, y, 1, name.c_str(), frame);
		}

		void draw(Vector pos, std::string name, int frame) {
			draw(pos.x, pos.y, 1, name.c_str(), frame);
		}

		void draw(Vector pos, const char * name, int frame) {
			draw(pos.x, pos.y, 1, name, frame);
		}

		void draw(Vector pos, double alpha, std::string name, int frame) {
			draw(pos.x, pos.y, alpha, name.c_str(), frame);
		}

		void draw(Vector pos, double alpha, const char * name, int frame) {
			draw(pos.x, pos.y, alpha, name, frame);
		}

		// more stuff

		/*void spriteLoad(const char * name, const char * file) {
			::sf::Texture * texture = new ::sf::Texture;
			if (!texture -> loadFromFile(file)) {
				std::cout << "Failed to load image file: " << file << std::endl;
				throw FlexiumException("Failed to load image file");
			}
			texture -> setSmooth(true);
			texture -> setRepeated(false);
			textures[name] = texture;
		}*/

		void drawPartial(Vector pos, Vector tex_pos, Vector tex_dim, ::sf::Texture * tex) {
			::sf::Sprite spr(*tex);
			spr.setPosition(pos.x, pos.y);
			spr.setTextureRect(::sf::IntRect(tex_pos.x, tex_pos.y, tex_dim.x, tex_dim.y));
			Window::getHandle() -> draw(spr);
		}

		void drawPartial(Vector pos, Vector tex_pos, Vector tex_dim, const char * name) {
			if (sprite_mapping.count(name) != 0) {
				if (sprite_mapping.count(name) == 1) {
					drawPartial(pos, tex_pos, tex_dim, sprite_mapping[name].texture);
				} else {
					Console::Error << "No texture named '" << name << "'" << std::endl;
				}
			} else {
				std::cout << "No sprite named: " << name << std::endl;
			}
		}

		int getWidth(const std::string& name) {
			if (sprite_mapping.count(name) == 0) return 0;
			return sprite_mapping[name].width;
		}

		int getHeight(const std::string& name) {
			if (sprite_mapping.count(name) == 0) return 0;
			return sprite_mapping[name].height;
		}

		::sf::Texture * getTexture(const char * name) {
			return sprite_mapping.count(name) == 0 ? nullptr : sprite_mapping[name].texture;
		}

	}

}