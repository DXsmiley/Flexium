#include <Flexium/World.hpp>
#include <Flexium/Object.hpp>
#include <Flexium/Window.hpp>
#include <Flexium/Sprite.hpp>
#include <Flexium/Input.hpp>
#include <Flexium/Audio.hpp>
#include <Flexium/Text.hpp>

int main() {

	Window::WindowSettings ws;
	Window::initiate(ws);

	Sprite::loadMapping("spritesheet.xml");
	Audio::loadMapping("soundsheet.xml");
	Text::loadMapping("fontsheet.xml");

	World w;
	while (w.simulate());

}