#include <Audio.hpp>
#include <Console.hpp>

#include <pugixml.hpp>

#include <map>

namespace Audio {

	class SoundSource {

		public:

			virtual void play() = 0;
			virtual void stop() = 0;
			virtual void load(const char *) = 0;

	};

	std::map<std::string, SoundSource *> mapping;

	class SoundSourceSFX : public SoundSource {

		private:

			sf::SoundBuffer buffer;
			sf::Sound sound;
			bool loaded;

		public:

			SoundSourceSFX() {
				loaded = false;
			}

			virtual void play() {
				if (loaded) sound.play();
			}

			virtual void stop() {
				if (loaded) sound.stop();
			}

			virtual void load(const char * filename) {
				if (buffer.loadFromFile(filename)) {
					sound.setBuffer(buffer);
					loaded = true;
				} else {
					Console::Error << "Failed to load sound file " << filename << std::endl;
				}
			}

	};

	class SoundSourceMusic : public SoundSource {

		private:

			sf::Music music;
			bool loaded;

		public:

			SoundSourceMusic() {
				loaded = false;
			}

			virtual void play() {
				if (loaded) music.play();
			}

			virtual void stop() {
				if (loaded) music.stop();
			}

			virtual void load(const char * filename) {
				if (music.openFromFile(filename)) {
					music.setLoop(true);
					loaded = true;
				} else {
					Console::Error << "Failed to load sound file " << filename << std::endl;
				}
			}

	};

	void loadMapping(const char * filename) {
		Console::Log << "Loading audio mapping from " << filename << std::endl;
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(filename);
		if (!result) {
			Console::Error << "An error occured while parsing sound list XML!" << std::endl;
		} else {
			pugi::xml_node root = doc.child("soundsheet");
			for (pugi::xml_node snd_node : root.children("sound")) {
				std::string snd_name = snd_node.attribute("name").value();
				std::string snd_source = snd_node.attribute("source").value();
				std::string snd_stream = snd_node.attribute("stream").value();
				if (snd_stream == "") {
					mapping[snd_name] = new SoundSourceSFX();
				} else {
					mapping[snd_name] = new SoundSourceMusic();
				}
				mapping[snd_name] -> load(snd_source.c_str());
			}
		}
	}

	void play(const char * name) {
		if (mapping[name] != NULL) {
			mapping[name] -> play();
		}
	}

	void stop(const char * name) {
		if (mapping[name] != NULL) {
			mapping[name] -> stop();
		}
	}

}