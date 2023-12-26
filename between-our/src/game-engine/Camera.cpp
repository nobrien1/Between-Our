#include "Camera.h"
#include "types.h"
#include "World.h"
#include "WorldObject.h"
#include "Texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ui/textGenerator.h"
#include "ui/uiHeader.h"

namespace gameEngine {

	Pointf Camera::transformPoint(Pointf p)
	{
		return Pointf((p.x - position.x) * scale, (p.y - position.y) * scale);
	}

	Dimensionf Camera::transformDimension(Dimensionf d) {
		return Dimensionf(d.width * scale, d.height * scale);
	}

	Camera::Camera() {}

	Dimensioni Camera::getWindowSize() {
		return windowSize;
	}

	void Camera::setWindowSize(Dimensioni size) {
		windowSize.width = size.width, windowSize.height = size.height;
	}

	void Camera::setWindowSize(int width, int height) {
		windowSize.width = width, windowSize.height = height;
	}

	void Camera::renderFrame(GLFWwindow* window, World* world) {
		glfwMakeContextCurrent(window);

		window::clear(Color3f(0, 0, 0));

		Texture* worldTexture = world->getTexture();
		worldTexture->draw(transformPoint(Pointf(0, 0)), transformDimension(world->getSize()));

		WorldObject** worldObjects = world->getWorldObjects();
		for (int i = 0; i < world->getWorldObjectCount(); i++) {
			WorldObject* worldObj = worldObjects[i];
			Pointf pos = worldObj->getPosition();
			worldObj->getTexture()->draw(transformPoint(pos), transformDimension(worldObj->getSize()));
		}
		for (int i = 0; i < world->getWorldObjectCount(); i++) {
			WorldObject* worldObj = worldObjects[i];
			Pointf pos = transformPoint(worldObj->getPosition());
			text::TextImage label = worldObj->getLabel();
			Pointf pos2 = Pointf(pos.x - label.size.width / 2.0 + worldObj->getSize().width / 2.0, pos.y + worldObj->getSize().height + 10);
			window::drawTextImage(pos2, label, worldObj->getLabelColor());
		}
	}

	void Camera::gameTick(double delta) {
		if (toFollow == NULL || toFollow == nullptr) return;

		float dx = toFollow->getPosition().x - position.x;
		float dy = toFollow->getPosition().y - position.y;
		move(dx * followSpeed * delta, dy * followSpeed * delta);

		if (zoomingIn) {
			scale *= 1 + 1 * delta * ZOOM_SPEED;
		}

		if (zoomingOut) {
			scale /= 1 + 1 * delta * ZOOM_SPEED;
		}
	}

	void Camera::follow(Positioned* p) {
		toFollow = p;
	}

	float Camera::getFollowSpeed() {
		return followSpeed;
	}

	void Camera::setFollowSpeed(float f) {
		followSpeed = f;
	}

	void Camera::setScale(float s) {
		scale = s;
	}

	float Camera::getScale() {
		return scale;
	}

	void Camera::setZoomingIn(bool z) {
		zoomingIn = z;
	}

	void Camera::setZoomingOut(bool z) {
		zoomingOut = z;
	}
}
