#include <Flexium/Input.hpp>
#include <Flexium/Flexium.hpp>
#include <Flexium/Window.hpp>

namespace flx {

	namespace Input {

		char keyboard[1024];
		char mouse[8];
		char char_typed;

		void update() {
			char_typed = '\0';
			const int to[] = {0, 2, 2, 0};
			for (unsigned int i = 0; i < Input::Key::KeyCount; i++) {
				keyboard[i] = to[(int)keyboard[i]];
			}
			for (unsigned int i = 0; i < ::sf::Mouse::ButtonCount; i++) {
				mouse[i] = to[(int)mouse[i]];
			}
			::sf::Event event;
			auto handle = Window::getHandle();
			while (handle -> pollEvent(event)) {
				if (event.type == ::sf::Event::Closed) handle -> close();
				if (event.type == ::sf::Event::Resized) {
					unsigned int w = event.size.width;
					unsigned int h = event.size.height;
					handle -> setSize(::sf::Vector2u(w, h));
				}
				if (event.type == ::sf::Event::KeyPressed) {
					int code = event.key.code;
					if (code != Key::Unknown) keyboard[code] = (keyboard[code] == 0 || keyboard[code] == 3) ? 1 : 2;
				}
				if (event.type == ::sf::Event::KeyReleased) {
					int code = event.key.code;
					if (code != Key::Unknown) keyboard[code] = 3;
				}
				if (event.type == ::sf::Event::MouseButtonPressed) {
					int code = event.mouseButton.button;
					//if (debug) std::cout << "Mouse button pressed " << code << std::endl;
					mouse[code] = (mouse[code] == 0 || mouse[code] == 3) ? 1 : 2;
				}
				if (event.type == ::sf::Event::MouseButtonReleased) {
					int code = event.mouseButton.button;
					//if (debug) std::cout << "Mouse button released " << code << std::endl;
					mouse[code] = 3;
				}
				if (event.type == ::sf::Event::TextEntered) {
					if (event.text.unicode < 128) {
						char_typed = (char)event.text.unicode;
					}
				}
			}
		}

		void keyCheckRange(int k) {
			if (k < 0 || k >= Key::KeyCount) {
				throw FlexiumException("Key code out of range");
			}
		}

		bool keyDown(int k) {
			keyCheckRange(k);
			return keyboard[k] == 1 || keyboard[k] == 2;
		}

		bool keyPressed(int k) {
			keyCheckRange(k);
			return keyboard[k] == 1;
		}

		bool keyReleased(int k) {
			keyCheckRange(k);
			return keyboard[k] == 3;
		}

		bool keyDownEx(int k) {
			bool v = false;
			switch (k) {
				case Key::ExShift: v = keyDown(Key::LShift) || keyDown(Key::RShift); break;
				case Key::ExControl: v = keyDown(Key::LControl) || keyDown(Key::RControl); break;
				case Key::ExAlt: v = keyDown(Key::LAlt) || keyDown(Key::RAlt); break;
				case Key::ExSystem: v = keyDown(Key::LSystem) || keyDown(Key::RSystem); break;
				default: v = keyDown(k); break;
			}
			return v;
		}

		bool keyPressedEx(int k) {
			bool v = false;
			switch (k) {
				case Key::ExShift: v = keyPressed(Key::LShift) || keyPressed(Key::RShift); break;
				case Key::ExControl: v = keyPressed(Key::LControl) || keyPressed(Key::RControl); break;
				case Key::ExAlt: v = keyPressed(Key::LAlt) || keyPressed(Key::RAlt); break;
				case Key::ExSystem: v = keyPressed(Key::LSystem) || keyPressed(Key::RSystem); break;
				default: v = keyPressed(k); break;
			}
			return v;
		}

		bool keyReleasedEx(int k) {
			bool v = false;
			switch (k) {
				case Key::ExShift: v = keyReleased(Key::LShift) || keyReleased(Key::RShift); break;
				case Key::ExControl: v = keyReleased(Key::LControl) || keyReleased(Key::RControl); break;
				case Key::ExAlt: v = keyReleased(Key::LAlt) || keyReleased(Key::RAlt); break;
				case Key::ExSystem: v = keyReleased(Key::LSystem) || keyReleased(Key::RSystem); break;
				default: v = keyReleased(k); break;
			}
			return v;
		}

		char characterTyped() {
			return char_typed;
		}

		bool mouseDown(int k) {
			return mouse[k] == 1 || mouse[k] == 2;
		}

		bool mousePressed(int k) {
			return mouse[k] == 1;
		}

		bool mouseReleased(int k) {
			return mouse[k] == 3;
		}

		double mouseX() {
			return ::sf::Mouse::getPosition(*Window::getHandle()).x;
		}

		double mouseY() {
			return ::sf::Mouse::getPosition(*Window::getHandle()).y;
		}

	}

}
