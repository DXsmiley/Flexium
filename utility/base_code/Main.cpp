#include <Flexium/World.hpp>
#include <Flexium/Window.hpp>
#include <Flexium/Sprite.hpp>
#include <Flexium/Audio.hpp>
#include <Flexium/Text.hpp>
#include <Flexium/Console.hpp>
#include <Flexium/FlexiumUtility.hpp>

int main() {

	flx::Window::WindowSettings ws;
	ws.title = "Window Title";
	flx::Window::initiate(ws);

	flx::Sprite::loadMapping("spritesheet.xml");
	flx::Audio::loadMapping("soundsheet.xml");
	flx::Text::loadMapping("fontsheet.xml");

	flx::World world;
	world.instanceAdd(new flx::Debugger());
	world.instanceAdd(new flx::ConsoleInGame());
	while (world.simulate());

}