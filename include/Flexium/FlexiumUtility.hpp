#ifndef FLEXIUM_UTILITY_H
#define FLEXIUM_UTILITY_H

#include <Flexium/Flexium.hpp>
#include <Flexium/Object.hpp>
#include <Flexium/Event.hpp>
#include <Flexium/Timer.hpp>

#include <cmath>

namespace flx {

	template <typename T>
	T clamp(T val, T small, T large) {
		return std::max(std::min(val, large), small);
	}

	void spritesLoadSpriteSheet(const char * filename);

	class EventPrint: public Event {

		private:

			std::string text;

		public:

			EventPrint(std::string t): Event(), text(t) {};
			virtual void trigger();
			virtual ~EventPrint() {};

	};

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
			Event * click_event;

		public:

			SimpleButton(std::string spr, Event * ce): Button(), image(spr), click_event(ce) {};

			virtual void onCreate();
			virtual void onClick();
			virtual void onDraw();
			virtual ~SimpleButton() {};

	};

	class Camera: public Object {

		protected:

			double zoom;

		public:

			Camera();
			double& getZoom();
			void setZoom(double z);
			virtual void onUpdate();
			virtual ~Camera() {};

	};

	class Tweener: public Object {

		public:

			enum Type {
				EASE_IN,
				EASE_OUT,
				EASE_BOTH
			};

			enum Loop {
				LOOP_NONE,
				LOOP_NORMAL,
				LOOP_REVERSE
			};

			class Algorithm {

				public:

					virtual double f(double t);
					virtual ~Algorithm() {};

			};

			class AlgorithmPower : public Algorithm {

				private:

					double e;

				public:

					AlgorithmPower(double exponent): e(exponent) {};

					virtual double f(double t);
					virtual ~AlgorithmPower() {};

			};

		private:

			double * value;
			double v_start;
			double v_end;
			double ticks;
			double ticks_delay;
			double ticks_count;
			Type type;
			Loop loop;
			Algorithm * algorithm;

			double ease_in(double);
			double ease_out(double);

		public:

			Tweener(double * value, double start, double end, double length, Type type, Algorithm * algorithm);
			Tweener(double * value, double start, double end, double length, Type type, Loop loop, Algorithm * algorithm);
			Tweener(double * value, double start, double end, double delay, double length, Type type, Algorithm * algorithm);
			Tweener(double * value, double start, double end, double delay, double length, Type type, Loop loop, Algorithm * algorithm);

			virtual void onUpdate();


	};

	class Debugger : public Object {

		private:

			bool cursor_spr;

		public:

			virtual void onCreate();
			virtual void onUpdate();
			virtual void onDraw();
			virtual ~Debugger() {};

	};

}

#endif