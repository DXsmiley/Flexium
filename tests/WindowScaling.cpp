#include <Flexium/World.hpp>
#include <Flexium/Object.hpp>
#include <Flexium/Window.hpp>
#include <Flexium/Sprite.hpp>
#include <Flexium/Input.hpp>
#include <Flexium/Audio.hpp>
#include <Flexium/Text.hpp>
#include <Flexium/FlexiumUtility.hpp>

using namespace flx;

class Image: public Object {

	public:

		virtual void onCreate() {
			setDimensionsToSprite("image");
			setOriginCentre();
		}

		virtual void onDraw() {
			Sprite::draw(boundTopLeft(), "image");
		}

};

int main() {

	Window::WindowSettings ws;
	ws.allow_resize = true;
	Window::initiate(ws);
	Sprite::load("image", "image.png");

	World w;

	Camera * camera = new Camera();
	w.instanceAdd(camera);
	w.instanceAdd(new Tweener(&camera -> getZoom(), 0.3, 3, 100, Tweener::EASE_BOTH, Tweener::LOOP_REVERSE, new Tweener::AlgorithmPower(2)));
	w.instanceAdd(new Image()) -> setPosition(0, 0);
	
	while (w.simulate());

}