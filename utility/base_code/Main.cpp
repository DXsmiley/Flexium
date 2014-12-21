#include <World.hpp>
#include <Object.hpp>
#include <Window.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <Audio.hpp>
#include <Text.hpp>

int main() {

	Window::WindowSettings ws;
	Window::initiate(ws);
	Window::setFrameRateLimit(60);

	Sprite::loadMapping("spritesheet.xml");
	Audio::loadMapping("soundsheet.xml");
	Text::loadMapping("fontsheet.xml");

	World w;
	while (w.simulate());

}