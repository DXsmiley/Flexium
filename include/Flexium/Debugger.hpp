#ifndef FLEXIUM_DEBUGGER_HPP
#define FLEXIUM_DEBUGGER_HPP

#include <Flexium/Object.hpp>

namespace flx {
	
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