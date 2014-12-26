#include <Flexium/Text.hpp>
#include <Flexium/Console.hpp>
#include <Flexium/pugixml.hpp>

namespace flx {

	namespace Text {

		std::map<std::string, ::sf::Font *> fonts;

		void loadMapping(const char * filename) {
			Console::Log << "Loading font mapping from " << filename << std::endl;
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_file(filename);
			if (!result) {
				Console::Error << "An error occured while parsing font list XML!" << std::endl;
			} else {
				pugi::xml_node root = doc.child("fontsheet");
				for (pugi::xml_node snd_node : root.children("font")) {
					std::string snd_name = snd_node.attribute("name").value();
					std::string snd_source = snd_node.attribute("source").value();
					Console::Log << "Font: " << snd_name << ' ' << snd_source << std::endl;
					loadFont(snd_name.c_str(), snd_source.c_str());
				}
			}
		}

		void loadFont(const char * n, const char * f) {
			::sf::Font * font = new ::sf::Font;
			if (!font -> loadFromFile(f)) {
				Console::Error << "Failed to load font file: " << f << std::endl;
				throw FlexiumException(std::string("Failed to load font file: ") + std::string(f));
			}
			fonts[n] = font;
		}

		::sf::Font * getFont(const char * fontname) {
			return fonts[fontname];
		}

		void draw(double x, double y, std::string mystring, const char * font, int fontsize, const ::sf::Color& colour) {
			::sf::Font * the_font = fonts[font];
			if (the_font == NULL) throw FlexiumException("Font does not exist!");
			::sf::Text text;
			text.setString(mystring);
			text.setPosition(x, y);
			text.setFont(*the_font);
			text.setCharacterSize(fontsize);
			text.setColor(colour);
			Window::getHandle() -> draw(text);
		}

		void draw(double x, double y, std::string mystring, const char * fontname, int size) {
			draw(x, y, mystring, fontname, size, ::sf::Color::Red);
		}

		void draw(Vector pos, std::string mystring, const char * font, int size) {
			draw(pos.x, pos.y, mystring, font, size, ::sf::Color::Red);
		}

		
		void draw(Vector pos, std::string mystring, const char * font, int size, const ::sf::Color& colour) {
			draw(pos.x, pos.y, mystring, font, size, colour);
		}

	}

}