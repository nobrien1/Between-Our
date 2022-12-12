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
	void Camera::drawRect(Pointf topLeft, Dimensionf size, Color3f color) {
		Pointf p(topLeft.x - position.x, topLeft.y - position.y);
		window::drawRect(p, size, color);
	}

	Pointf Camera::transformPoint(Pointf p)
	{
		return Pointf(p.x - position.x, p.y - position.y);
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
		worldTexture->draw(transformPoint(Pointf(0, 0)), world->getSize());

		WorldObject** worldObjects = world->getWorldObjects();
		for (int i = 0; i < world->getWorldObjectCount(); i++) {
			WorldObject* worldObj = worldObjects[i];
			Pointf pos = worldObj->getPosition();
			worldObj->getTexture()->draw(transformPoint(pos), worldObj->getSize());
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
		if (toFollow == NULL) return;

		float dx = toFollow->getPosition().x - position.x;
		float dy = toFollow->getPosition().y - position.y;
		move(dx * followSpeed * delta, dy * followSpeed * delta);
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
}

