#ifndef FLEXIUM_UTILITY_H
#define FLEXIUM_UTILITY_H

#include <Flexium/Flexium.hpp>
#include <Flexium/Object.hpp>
#include <Flexium/Event.hpp>
#include <Flexium/Timer.hpp>

// Not required, but in here for compatibility reasons
#include <Flexium/Tweener.hpp>
#include <Flexium/Debugger.hpp>
#include <Flexium/Camera.hpp>
#include <Flexium/ExtraEvents.hpp>

#include <cmath>
#include <vector>
#include <initializer_list>

namespace flx {

	template <typename T>
	T clamp(T val, T small, T large) {
		return std::max(std::min(val, large), small);
	}

	class Button: public Object {

		protected:

			bool hovering;

		public:

			Button(): hovering(false) {};

			virtual void onUpdate();
			virtual void onClick() {};
			virtual void onHover() {};
			virtual void onLeave() {};
			virtual ~Button() {};

	};

	class SimpleButton: public Button {

		protected:

			std::string image;
			std::shared_ptr<Event> click_event;

		public:

			SimpleButton(std::string spr, Event * ce): Button(), image(spr), click_event(ce) {};

			virtual void onCreate();
			virtual void onClick();
			virtual void onDraw();
			virtual ~SimpleButton() {};

	};

}

#endif