#include <Flexium/Tweener.hpp>
#include <Flexium/FlexiumUtility.hpp>

namespace flx {

	Tweener::Tweener(double * v, double s, double e, double d, double l, Type t, Algorithm * a) {
		value = v;
		v_start = s;
		v_end = e;
		ticks = l;
		ticks_delay = d;
		ticks_count = 0;
		algorithm = a;
		type = t;
		loop = LOOP_NONE;
	}

	Tweener::Tweener(double * v, double s, double e, double d, double l, Type t, Loop k, Algorithm * a) {
		value = v;
		v_start = s;
		v_end = e;
		ticks = l;
		ticks_delay = d;
		ticks_count = 0;
		algorithm = a;
		type = t;
		loop = k;
	}

	Tweener::Tweener(double * v, double s, double e, double l, Type t, Algorithm * a) {
		value = v;
		v_start = s;
		v_end = e;
		ticks = l;
		ticks_count = 0;
		algorithm = a;
		type = t;
		loop = LOOP_NONE;
		ticks_delay = 0;
	}

	Tweener::Tweener(double * v, double s, double e, double l, Type t, Loop k, Algorithm * a) {
		value = v;
		v_start = s;
		v_end = e;
		ticks = l;
		ticks_count = 0;
		algorithm = a;
		type = t;
		loop = k;
		ticks_delay = 0;
	}

	double Tweener::ease_in(double t) {
		return algorithm -> f(t);
	}

	double Tweener::ease_out(double t) {
		return 1.0 - (algorithm -> f(1.0 - t));
	}

	void Tweener::onUpdate() {
		if (algorithm) {
			ticks_count += 1.0;
			if (ticks_count >= ticks_delay) {
				double t = (ticks_count - ticks_delay) / ticks;
				if (t >= 1.0 && loop == LOOP_REVERSE) {
					t = 2.0 - t;
				}
				t = clamp(t, 0.0, 1.0);
				//std::cout << ticks << ticks_count << t << ' ';
				double f = 0;
				if (type == EASE_IN) f = ease_in(t);
				if (type == EASE_OUT) f = ease_out(t);
				if (type == EASE_BOTH) f = t < 0.5 ? ease_in(2.0 * t) / 2.0 : 0.5 + (ease_out(2 * t - 1) / 2);
				*value = v_start + (f * (v_end - v_start));
				if (ticks_count >= ticks + ticks_delay) {
					if (loop == LOOP_NONE) {
						*value = v_end;
						destroy();
						delete algorithm;
						algorithm = nullptr;
					}
					if (loop == LOOP_NORMAL) {
						ticks_count = ticks_delay;
					}
				}
				if (loop == LOOP_REVERSE && ticks_count >= (ticks * 2) + ticks_delay) {
					ticks_count = ticks_delay;
				}
			}
		}
	}

	double Tweener::Algorithm::f(double t) {
		return t;
	}

	double Tweener::AlgorithmPower::f(double t) {
		return pow(t, e);
	}

}