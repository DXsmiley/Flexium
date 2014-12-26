#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <vector>

namespace flx {

	namespace Random {

		void setSeed();
		void setSeed(unsigned int);

		int integer(); // [0, RAND_MAX)
		int integer(int); // [0, a)
		int integer(int, int); // [a, b)

		double real(); // [0, 1)
		double real(double); // [0, a)
		double real(double, double); // [a, b)

		bool boolean();

		template <typename T>
		const T& pick(std::initializer_list<T> list) {
			int size = (int)list.size();
			int place = integer(size);
			for (const T& n : list) {
				if (place == 0) return n;
				place--;
			}
			return (*list.begin());
		}

		unsigned int weighted(const std::vector<unsigned int>&);

	};

}

#endif