#ifndef FLEXIUM_MEMORY_HPP
#define FLEXIUM_MEMORY_HPP

#include <memory>

namespace flx {

	/**
		This is similar to an std::shared_ptr, however it will perform some automatic casts.
		@see Object::collidesWith for example usage
	*/
	template <typename T>
	class shared_ptr_autocast {

		private:

			std::shared_ptr<T> my_ptr;

		public:

			template <typename U>
			shared_ptr_autocast(std::shared_ptr<U> new_ptr) {
				my_ptr = std::dynamic_pointer_cast<T>(new_ptr);
			}

			// @warning I'm not sure this is safe. I should run some checks on it at some point.
			template <typename U>
			shared_ptr_autocast(U * new_ptr) {
				if (new_ptr != nullptr) {
					my_ptr = std::shared_ptr<T>(dynamic_cast<T*>(new_ptr));
					// if (my_ptr == nullptr) {
					// 	flx::Console::Error << "Could not perform cast!" << std::endl;
					// }
				}
			}

			std::shared_ptr<T> operator->() {
				return my_ptr;
			}

			bool operator != (std::nullptr_t) {
				return my_ptr != nullptr;
			}

			bool operator == (std::nullptr_t) {
				return my_ptr == nullptr;
			}

			std::nullptr_t operator = (std::nullptr_t) {
				my_ptr = nullptr;
				return nullptr;
			}

	};

};

#endif