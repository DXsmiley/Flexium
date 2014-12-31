#include <Flexium/World.hpp>
#include <Flexium/Object.hpp>
#include <Flexium/Window.hpp>
#include <Flexium/Sprite.hpp>
#include <Flexium/Input.hpp>
#include <Flexium/Audio.hpp>
#include <Flexium/Text.hpp>
#include <Flexium/FlexiumUtility.hpp>
#include <Flexium/Console.hpp>

using namespace flx;

class ObjectDemo : public Object {

	private:

		Vector velocity;
		int anim_frame;
		bool anim;

	public:

		ObjectDemo(): velocity(4, 4), anim(false) {};

		virtual void onCreate() {
			setDimensionsToSprite("image");
		}

		virtual void onUpdate() {
			bool bounced = false;
			position += velocity;
			if (position.x < 0) {
				velocity.x = 4;
				bounced = true;
			}
			if (position.x > 800) {
				velocity.x = -4;
				bounced = true;
			}
			if (position.y < 0) {
				velocity.y = 4;
				bounced = true;
			}
			if (position.y > 400) {
				velocity.y = -4;
				bounced = true;
			}
			if (bounced) {
				Audio::play("sound");
			}
			if (Input::keyPressed(Input::Key::Space)) {
				velocity *= 4;
				anim = !anim;
			}
			anim_frame++;
		}

		virtual void onDraw() {
			Sprite::draw(position, "image");
			Sprite::draw(30, 100, anim ? "animation" : "animation2", anim_frame / 4);
			Text::draw(30, 30, "Flexium minimalistic demo. Try pressing space.", "font", 32, sf::Color::White);
		}

};

int main() {

	Window::WindowSettings ws;
	ws.title = "Flexium Demo";
	Window::initiate(ws);
	Window::setFrameRateLimit(60);

	Sprite::loadMapping("spritesheet.xml");
	Audio::loadMapping("soundsheet.xml");
	Text::loadMapping("fontsheet.xml");

	World w;
	w.instanceAdd(new Debugger());
	w.instanceAdd(new ConsoleInGame());
	w.instanceAdd(new ObjectDemo());
	while (w.simulate());

}