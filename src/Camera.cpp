#include <Flexium/Camera.hpp>
#include <Flexium/Window.hpp>

namespace flx {

	Camera::Camera() {
		zoom = 1;
		setDepth(1);
	}

	Camera::Camera(int depth) {
		zoom = 1;
		setDepth(depth);
	}

	void Camera::onUpdate() {
		Window::viewSetZoom(zoom);
		Window::viewSetPosition(position);
	}

	double& Camera::getZoom() {
		return zoom;
	}

	void Camera::setZoom(double z) {
		zoom = z;
	}

	void CameraCentre::onUpdate() {
		position.x = Window::getWidth() / 2;
		position.y = Window::getHeight() / 2;
		Camera::onUpdate();
	}

}