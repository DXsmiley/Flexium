#include "Object.hpp"
#include "Sprite.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

int Object::getID() const {
	return id;
}

void Object::registerWorld(int n, World * w) {
	if (id != 0 || my_world != NULL) throw FlexiumException("Attempted to re-register object!");
	id = n;
	my_world = w;
}

bool Object::isAlive() const {
	return alive;
}

bool Object::isActive() const {
	return active;
}

void Object::activate() {
	active = true;
}

void Object::deactivate() {
	active = false;
}

bool Object::isPersistent() const {
	return persistent;
}

void Object::setPersistent(bool p) {
	persistent = p;
}

World * Object::getWorld() const {
	return my_world;
}

int Object::getDepth() const {
	return depth;
}

void Object::setDepth(int d) {
	depth = d;
}

void Object::destroy() {
	alive = false;
}

void Object::setPosition(double x, double y) {
	position.x = x;
	position.y = y;
}

Vector Object::getPosition() {
	return position;
}

void Object::setPosition(Vector v) {
	position = v;
}

void Object::setDimensions(double x, double y) {
	dimensions.x = x;
	dimensions.y = y;
}

void Object::setDimensions(Vector v) {
	dimensions = v;
}

Vector& Object::getDimensions() {
	return dimensions;
}

void Object::setOriginCentre() {
	origin = Vector(0.5, 0.5);
}

void Object::setOrigin(double x, double y) {
	origin = Vector(x, y);
}

void Object::setOrigin(Vector v) {
	origin = v;
}

double Object::marginLeft() {
	return dimensions.x * origin.x;
}

double Object::marginRight() {
	return dimensions.x * (1.0 - origin.x);
}

double Object::marginTop() {
	return dimensions.y * origin.y;
}

double Object::marginBottom() {
	return dimensions.y * (1.0 - origin.y);
}

double Object::boundLeft() {
	return position.x - marginLeft();
}

double Object::boundRight() {
	return position.x + marginRight();
}

double Object::boundTop() {
	return position.y - marginTop();
}

double Object::boundBottom() {
	return position.y + marginBottom();
}

Vector Object::boundTopLeft() {
	return Vector(boundLeft(), boundTop());
}

Vector Object::boundTopRight() {
	return Vector(boundRight(), boundTop());
}

Vector Object::boundBottomLeft() {
	return Vector(boundLeft(), boundBottom());
}

Vector Object::boundBottomRight() {
	return Vector(boundRight(), boundBottom());
}

void Object::setDimensionsToSprite(const char * name) {
	sf::Texture * tex = Sprite::getTexture(name);
	if (tex) {
		sf::Vector2u dim = tex -> getSize();
		dimensions = Vector(dim.x, dim.y);
	}
}

void Object::setDimensionsToSprite(std::string name) {
	setDimensionsToSprite(name.c_str());
}

bool Object::collidesWith(Object * o) {
	return boundLeft() < o -> boundRight() && boundRight() > o -> boundLeft() && boundTop() < o -> boundBottom() && boundBottom() > o -> boundTop();
}