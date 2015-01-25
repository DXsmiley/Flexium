#ifndef FLEXIUM_TRANSFORM_HPP
#define FLEXIUM_TRANSFORM_HPP

#include <SFML/Graphics/Transform.hpp>
#include <Flexium/Vector.hpp>

namespace flx {

	namespace Transform {

		sf::Transform translate(double x, double y);
		sf::Transform translate(Vector position);
		sf::Transform rotate(double angle);
		sf::Transform scale(double x, double y);
		sf::Transform scale(Vector scale);

	}

}

#endif