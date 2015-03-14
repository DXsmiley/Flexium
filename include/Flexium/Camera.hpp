#ifndef FLEXIUM_CAMERA_HPP
#define FLEXIUM_CAMERA_HPP

#include <Flexium/Object.hpp>

namespace flx {

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
}

#endif