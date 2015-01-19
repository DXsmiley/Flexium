#ifndef FLEXIUM_MEMORY_HPP
#define FLEXIUM_MEMORY_HPP

#include <memory>

namespace flx {

	//This is an std::shared_ptr that will automatically cast other things to it.
	template <typename T>
	class shared_ptr_autocast {

		private:

			std::shared_ptr<T> my_ptr;

		public:

			template <typename U>
			shared_ptr_autocast(std::shared_ptr<U> new_ptr) {
				my_ptr = std::dynamic_pointer_cast<T>(new_ptr);
			}

			std::shared_ptr<T> operator->() {
				return my_ptr;
			}

	};

};

#endif