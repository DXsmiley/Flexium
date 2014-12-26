#ifndef FLEXIUM_AUDIO_HPP
#define FLEXIUM_AUDIO_HPP

#include <SFML/Audio.hpp>

namespace flx {

	namespace Audio {

		void loadMapping(const char *);

		void play(const char *);
		void stop(const char *);
		void playLooped(const char *);

	};

}

#endif