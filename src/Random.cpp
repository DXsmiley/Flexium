#include "Random.hpp"

#include <cstdlib>
#include <ctime>
#include <numeric>

namespace Random {

	void setSeed() {
		std::srand(std::time(NULL));
	}

	void setSeed(unsigned int seed) {
		std::srand(seed);
	}

	int integer() {
		return std::rand();
	}

	int integer(int maximum) {
		return std::rand() % maximum;
	}

	int integer(int minimum, int maximum) {
		return minimum + (std::rand() % (maximum - minimum));
	}

	double real() {
		return (double)std::rand() / (double)RAND_MAX;
	}

	double real(double maximum) {
		return maximum * real();
	}

	double real(double minimum, double maximum) {
		return minimum + real(maximum - minimum);
	}

	bool boolean() {
		return (std::rand() & 1) == 0;
	}

	unsigned int weighted(const std::vector<unsigned int>& vec) {
		unsigned int place = integer(std::accumulate(vec.begin(), vec.end(), 0));
		for (unsigned int i = 0; i < vec.size(); i++) {
			if (place < vec[i]) {
				return i;
			}
			place -= vec[i];
		}
		return 0;
	}


};