#include <Flexium/Window.hpp>
#include <Flexium/Flexium.hpp>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace flx {

	namespace Window {

		double view_height;
		double view_width;
		double view_zoom = 1;
		::sf::Color background_color;

		::sf::RenderWindow * window;

		WindowSettings WindowSettings::fullscreenMode(const std::string title = "Title") {
			WindowSettings s;
			::sf::VideoMode d = ::sf::VideoMode::getDesktopMode();
			s.width = d.width;
			s.height = d.height;
			s.fullscreen = true;
			s.title = title;
			s.framelimit = 60;
			s.allow_resize = false;
			return s;
		}

		::sf::RenderWindow * getHandle() {
			return window;
		}

		void initiate(WindowSettings s) {
			/*view_width = s.width;
			view_height = s.height;*/
			unsigned int style = ::sf::Style::None;
			if (s.fullscreen) {
				style |= ::sf::Style::Fullscreen;
			} else {
				 style |= ::sf::Style::Close | ::sf::Style::Titlebar;
				 if (s.allow_resize) {
				 	style |= ::sf::Style::Resize;
				 }
			}
			window = new ::sf::RenderWindow(::sf::VideoMode(s.width, s.height), s.title, style);
			if (s.framelimit != 0) {
				window -> setFramerateLimit(s.framelimit);
			} else {
				window -> setVerticalSyncEnabled(true);
			}
		}

		void close() {
			window -> close();
		}

		void setFrameRateLimit(int rate) {
			window -> setFramerateLimit(rate);
		}

		void setClearColor(::sf::Color c) {
			background_color = c;
		}

		void clear() {
			window -> clear(background_color);
		}

		void display() {
			window -> display();
		}

		unsigned int getWidth() {
			return window -> getSize().x;
		}

		unsigned int getHeight() {
			return window -> getSize().y;
		}

		void viewSetPosition(double x, double y) {
			::sf::View view = window -> getView();
			view.setSize(::sf::Vector2f(window -> getSize()));
			view.zoom(view_zoom);
			view.setCenter(x, y);
			window -> setView(view);
		}

		void viewSetPosition(Vector v) {
			viewSetPosition(v.x, v.y);
		}

		void viewSetPositionZero() {
			::sf::Vector2f s = window -> getView().getSize();
			//viewSetPosition(s.x / 2, s.y / 2);
			viewSetPosition(s.x, s.y);
		}

		Vector viewGetCentre() {
			::sf::Vector2f s = window -> getView().getCenter();
			return Vector(s.x, s.y);
		}

		void viewSetZoom(double f) {
			view_zoom = f;
		}

	}

}