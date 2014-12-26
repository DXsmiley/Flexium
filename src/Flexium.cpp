#include <Flexium/Flexium.hpp>
#include <Flexium/Console.hpp>
#include <Flexium/Sprite.hpp>
#include <Flexium/Input.hpp>
#include <Flexium/Window.hpp>

#include <sstream>

#include <SFML/Graphics.hpp>

/// System

namespace flx {

	bool debug;

	void assertStarted() {
		if (Window::getHandle() == NULL) throw FlexiumException("Flexium was not initiated");
	}

	void graphicDrawRectangleOutline(Vector pos, Vector dim) {
		::sf::RectangleShape rect;
		rect.setSize(::sf::Vector2f(dim.x, dim.y));
		rect.setPosition(pos.x, pos.y);
		rect.setFillColor(::sf::Color::Transparent);
		rect.setOutlineThickness(1);
		rect.setOutlineColor(::sf::Color::Red);
		Window::getHandle() -> draw(rect);
	}

	void graphicDrawRectangleOutline(Vector pos, Vector dim, ::sf::Color col) {
		::sf::RectangleShape rect;
		rect.setSize(::sf::Vector2f(dim.x, dim.y));
		rect.setPosition(pos.x, pos.y);
		rect.setFillColor(::sf::Color::Transparent);
		rect.setOutlineThickness(1);
		rect.setOutlineColor(col);
		Window::getHandle() -> draw(rect);	
	}

	/*
	::sf::View Window::getHandle()GetView() {
		return Window::getHandle() -> getView();
	}

	void Window::getHandle()SetView(::sf::View v) {
		Window::getHandle() -> setView(v);
	}

	int Window::getHandle()GetViewX() {
		return Window::getHandle() -> getView().getCenter().x;
	}

	int Window::getHandle()GetViewY() {
		return Window::getHandle() -> getView().getCenter().y;
	}

	int Window::getHandle()GetViewWidth() {
		return Window::getHandle() -> getView().getSize().x;
	}

	int Window::getHandle()GetViewHeight() {
		return Window::getHandle() -> getView().getSize().y;
	}
	*/

	/// Utility

	std::vector<std::string> split(std::string s, char delim) {
		std::vector<std::string> elems;
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

}