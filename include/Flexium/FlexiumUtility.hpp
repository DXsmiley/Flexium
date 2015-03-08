#ifndef FLEXIUM_UTILITY_H
#define FLEXIUM_UTILITY_H

#include <Flexium/Flexium.hpp>
#include <Flexium/Object.hpp>
#include <Flexium/Event.hpp>
#include <Flexium/Timer.hpp>

#include <cmath>
#include <vector>
#include <initializer_list>

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
			virtual void onTrigger();
			virtual ~EventPrint() {};

	};

	class EventCreate : public Event {

		private:

			std::shared_ptr<Object> obj;

		private:

			EventCreate(std::shared_ptr<Object> o): obj(o) {};
			virtual void onTrigger();
			virtual ~EventCreate() {};

	};

	class EventDestroy : public Event {

		private:

			std::shared_ptr<Object> obj;

		public:

			EventDestroy(std::shared_ptr<Object> o): obj(o) {};
			virtual void onTrigger();
			virtual ~EventDestroy() {};

	};

	class EventCompond : public Event {

		private:

			std::vector<std::shared_ptr<Event> > events;

		public:

			EventCompond(std::initializer_list<std::shared_ptr<Event> >);
			// EventCompond(std::initializer_list<Event*>);
			virtual void onTrigger();
			virtual ~EventCompond();

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
			std::shared_ptr<Event> click_event;

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
			Camera(int);
			double& getZoom();
			void setZoom(double z);
			virtual void onUpdate();
			virtual ~Camera() {};

	};

	class CameraCentre : public Camera {

		public:

			virtual void onUpdate();
			virtual ~CameraCentre() {};

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

					AlgorithmPower(): e(2) {};
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