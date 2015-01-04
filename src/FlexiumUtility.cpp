#include <Flexium/FlexiumUtility.hpp>
#include <Flexium/Console.hpp>
#include <Flexium/Input.hpp>
#include <Flexium/Sprite.hpp>
#include <Flexium/pugixml.hpp>
#include <Flexium/World.hpp>

namespace flx {

	void EventPrint::trigger() {
		std::cout << text << std::endl;
	}

	void Timer::onUpdate() {
		if (isAlive() && event) {
			if (mytime == 0) {
				event -> setWorld(getWorld());
				event -> trigger();
				delete event;
				event = NULL;
				destroy();
			} else {
				mytime--;
			}
		}
	}

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
		if (click_event != NULL) {
			if (click_event -> getWorld() == NULL) {
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

	Camera::Camera() {
		zoom = 1;
		setDepth(1);
	}

	void Camera::onUpdate() {
		Window::viewSetPosition(position);
		Window::viewSetZoom(zoom);
	}

	double& Camera::getZoom() {
		return zoom;
	}

	void Camera::setZoom(double z) {
		zoom = z;
	}

	void CameraCentre::onUpdate() {
		position.x = Window::getWidth() / 2;
		position.y = Window::getHeight() / 2;
		Camera::onUpdate();
	}

	Tweener::Tweener(double * v, double s, double e, double d, double l, Type t, Algorithm * a) {
		value = v;
		v_start = s;
		v_end = e;
		ticks = l;
		ticks_delay = d;
		ticks_count = 0;
		algorithm = a;
		type = t;
		loop = LOOP_NONE;
	}

	Tweener::Tweener(double * v, double s, double e, double d, double l, Type t, Loop k, Algorithm * a) {
		value = v;
		v_start = s;
		v_end = e;
		ticks = l;
		ticks_delay = d;
		ticks_count = 0;
		algorithm = a;
		type = t;
		loop = k;
	}

	Tweener::Tweener(double * v, double s, double e, double l, Type t, Algorithm * a) {
		value = v;
		v_start = s;
		v_end = e;
		ticks = l;
		ticks_count = 0;
		algorithm = a;
		type = t;
		loop = LOOP_NONE;
		ticks_delay = 0;
	}

	Tweener::Tweener(double * v, double s, double e, double l, Type t, Loop k, Algorithm * a) {
		value = v;
		v_start = s;
		v_end = e;
		ticks = l;
		ticks_count = 0;
		algorithm = a;
		type = t;
		loop = k;
		ticks_delay = 0;
	}

	double Tweener::ease_in(double t) {
		return algorithm -> f(t);
	}

	double Tweener::ease_out(double t) {
		return 1.0 - (algorithm -> f(1.0 - t));
	}

	void Tweener::onUpdate() {
		if (algorithm) {
			ticks_count += 1.0;
			if (ticks_count >= ticks_delay) {
				double t = (ticks_count - ticks_delay) / ticks;
				if (t >= 1.0 && loop == LOOP_REVERSE) {
					t = 2.0 - t;
				}
				t = clamp(t, 0.0, 1.0);
				//std::cout << ticks << ticks_count << t << ' ';
				double f = 0;
				if (type == EASE_IN) f = ease_in(t);
				if (type == EASE_OUT) f = ease_out(t);
				if (type == EASE_BOTH) f = t < 0.5 ? ease_in(2.0 * t) / 2.0 : 0.5 + (ease_out(2 * t - 1) / 2);
				*value = v_start + (f * (v_end - v_start));
				if (ticks_count >= ticks + ticks_delay) {
					if (loop == LOOP_NONE) {
						*value = v_end;
						destroy();
						delete algorithm;
						algorithm = NULL;
					}
					if (loop == LOOP_NORMAL) {
						ticks_count = ticks_delay;
					}
				}
				if (loop == LOOP_REVERSE && ticks_count >= (ticks * 2) + ticks_delay) {
					ticks_count = ticks_delay;
				}
			}
		}
	}

	double Tweener::Algorithm::f(double t) {
		return t;
	}

	double Tweener::AlgorithmPower::f(double t) {
		return pow(t, e);
	}

	void Debugger::onCreate() {
		setDepth(100);
		setMeta(true);
		setPersistent(true);
		cursor_spr = false;
		// Try and load a cursor sprite if none are supplied.
		try {
			if (Sprite::getTexture("debug_cursor") == NULL) {
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
		/*if (debug) {
			if (Input::mousePressed(::sf::Mouse::Left)) {
				std::cout << "Left mouse button pressed" << std::endl;
			}
			if (Input::mousePressed(::sf::Mouse::Right)) {
				std::cout << "Right mouse button pressed" << std::endl;
			}
		}*/
	}

	void Debugger::onDraw() {
		if (debug) {
			if (cursor_spr) {
				Sprite::draw(Input::mouseX(), Input::mouseY(), "debug_cursor");
			}
			for (auto o : getWorld() -> instanceGet<Object*>()) {
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