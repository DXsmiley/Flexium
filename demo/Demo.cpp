#include <World.hpp>
#include <Object.hpp>
#include <Window.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <Audio.hpp>
#include <Text.hpp>

class ObjectDemo : public Object {

	private:

		Vector velocity;
		int anim_frame;
		bool anim;

	public:

		ObjectDemo(): velocity(4, 4), anim(false) {};

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
			Text::draw(30, 30, "Flexium minimalistic demo. Try pressing space.", "font", 32);
		}

};

int main() {

	Window::WindowSettings ws;
	Window::initiate(ws);
	Window::setFrameRateLimit(60);

	Sprite::loadMapping("spritesheet.xml");
	Audio::loadMapping("soundsheet.xml");
	Text::loadMapping("fontsheet.xml");

	World w;
	w.instanceAdd(new ObjectDemo());
	while (w.simulate());

}