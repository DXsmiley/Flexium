#include <Flexium/FlexiumUtility.hpp>
#include <Flexium/Console.hpp>
#include <Flexium/Input.hpp>
#include <Flexium/Sprite.hpp>
#include <Flexium/pugixml.hpp>
#include <Flexium/World.hpp>

namespace flx {

	void Button::onUpdate() {
		double mx = Input::mouseX() - position.x;
		double my = Input::mouseY() - position.y;
		if (mx > -marginLeft() && mx < marginRight() && my > -marginTop() && my < marginBottom()) {
			if (!hovering) {
				hovering = true;
				onHover();
			}
			if (Input::mousePressed(::sf::Mouse::Left)) {
				onClick();
			}
		} else {
			if (hovering) {
				hovering = false;
				onLeave();
			}
		}
	}

	void SimpleButton::onCreate() {
		origin = Vector(0.5, 0.5);
		setDimensionsToSprite(image);
	}

	void SimpleButton::onClick() {
		Console::Log << "SimpleButton::onClick()" << std::endl;
		if (click_event != nullptr) {
			if (click_event -> getWorld() == nullptr) {
				click_event -> setWorld(getWorld());
			}
			click_event -> trigger();
		}
	}

	void SimpleButton::onDraw() {
		Sprite::draw(boundTopLeft(), image);
		// if (debug) {
		// 	graphicDrawRectangleOutline(Vector(position.x - marginLeft(), position.y - marginTop()), dimensions);
		// }
	}

}