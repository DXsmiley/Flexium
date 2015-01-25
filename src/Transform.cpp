#include <Flexium/Transform.hpp>

namespace flx {

	namespace Transform {

		sf::Transform translate(double x, double y) {
			sf::Transform t;
			t.translate(x, y);
			return t;
		}

		sf::Transform translate(Vector position) {
			sf::Transform t;
			t.translate(position.x, position.y);
			return t;
		}

		sf::Transform rotate(double angle) {
			sf::Transform t;
			t.rotate(angle);
			return t;
		}

		sf::Transform scale(double x, double y) {
			sf::Transform t;
			t.scale(x, y);
			return t;
		}

		sf::Transform scale(Vector scale) {
			sf::Transform t;
			t.scale(scale.x, scale.y);
			return t;
		}

	}

}