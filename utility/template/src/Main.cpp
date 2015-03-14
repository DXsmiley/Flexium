/*

	This is a simple main file for starting your own project from.


*/

#include <Flexium/World.hpp>
#include <Flexium/Window.hpp>
#include <Flexium/Sprite.hpp>
#include <Flexium/Audio.hpp>
#include <Flexium/Text.hpp>
#include <Flexium/Console.hpp>
#include <Flexium/Debugger.hpp>

int main() {

	// Create the window
	flx::Window::WindowSettings ws;
	ws.title = "Window Title";
	flx::Window::setClearColor(sf::Color::White);
	flx::Window::initiate(ws);

	// Load resources
	flx::Sprite::loadMapping("spritesheet.xml");
	flx::Audio::loadMapping("soundsheet.xml");
	flx::Text::loadMapping("fontsheet.xml");

	// Setup the world
	// When you release your game, you should disable the debugger
	// and in-game console.
	flx::World world;
	world.instanceAdd(new flx::Debugger());
	world.instanceAdd(new flx::ConsoleInGame());
	while (world.simulate());

}