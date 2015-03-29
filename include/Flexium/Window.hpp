#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

namespace sf {
	class RenderWindow;
	class Color;
}

namespace flx {

	class Vector;

	namespace Window {

		/**
			Used to specify the parameters used when creating a window.
		*/
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

		/**
			Get the sfml handle for the window.
		*/
		::sf::RenderWindow * getHandle();

		/**
			Create the window.
			\param params Parameters used for creating the window. 
			\sa WindowSettings
		*/
		void initiate(WindowSettings params);

		/**
			Close the window.
		*/
		void close();

		/**
			Set the frame rate limit of the window.
		*/
		void setFrameRateLimit(int);

		/**
			Sets the colour that is used to clear the window every frame.
		*/
		void setClearColor(::sf::Color);

		/**
			Clear the window.
		*/
		void clear();
		
		/**
			Update the window.
		*/
		void display();

		/**
			Get the width of the window.
		*/
		unsigned int getWidth();
		
		/**
			Get the height of the window.
		*/
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