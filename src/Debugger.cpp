#include <Flexium/Debugger.hpp>
#include <Flexium/Input.hpp>
#include <Flexium/Sprite.hpp>
#include <Flexium/World.hpp>

#include <iostream>

namespace flx {
	
	void Debugger::onCreate() {
		setDepth(100);
		setMeta(true);
		setPersistent(true);
		cursor_spr = false;
		// Try and load a cursor sprite if one isn't supplied.
		try {
			if (Sprite::getTexture("debug_cursor") == nullptr) {
				Sprite::load("debug_cursor", "images/debug_cursor.png");
			}
			cursor_spr = true;
		} catch (FlexiumException& e) {}
	}

	void Debugger::onUpdate() {
		if (Input::keyPressed(Input::Key::Tilde)) {
			debug = !debug;
			std::cout << (debug ? "Debug mode activated" : "Debug mode deactivated") << std::endl;
		}
	}

	void Debugger::onDraw() {
		if (debug) {
			if (cursor_spr) {
				Sprite::draw(Input::mouseX(), Input::mouseY(), "debug_cursor");
			}
			for (auto o : getWorld() -> instanceGet<Object>()) {
				Vector tl = o -> boundTopLeft();
				Vector dm = o -> getDimensions();
				sf::Color col(128, 128, 128);
				if (Input::mouseX() > tl.x && Input::mouseX() < tl.x + dm.x && Input::mouseY() > tl.y && Input::mouseY() < tl.y + dm.y) {
					col = sf::Color::Red;
				}
				graphicDrawRectangleOutline(tl, dm, col);
			}
		}
	}

}