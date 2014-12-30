#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

namespace sf {
	class RenderWindow;
}

namespace flx {

	class Vector;

	namespace Window {

		struct WindowSettings {

			unsigned int width;
			unsigned int height;
			bool fullscreen;
			std::string title;
			unsigned int framelimit;
			bool allow_resize;

			WindowSettings(): width(800), height(640), fullscreen(false), title("Title"), framelimit(60), allow_resize(false) {};

			static WindowSettings fullscreenMode(const std::string);

		};

		::sf::RenderWindow * getHandle();
		void initiate(WindowSettings);
		void setFrameRateLimit(int);
		void close();

		unsigned int getWidth();
		unsigned int getHeight();

		void viewSetPosition(double x, double y);
		void viewSetPosition(Vector);
		void viewSetPositionZero();

		Vector viewGetPosition();
		Vector viewGetCentre();

		void viewSetZoom(double f);

	};

}

#endif