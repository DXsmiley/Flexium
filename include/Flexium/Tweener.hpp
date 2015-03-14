#ifndef FLEXIUM_TWEENER_HPP
#define FLEXIUM_TWEENER_HPP

#include <Flexium/Object.hpp>

namespace flx {

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

}

#endif