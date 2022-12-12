#include "Positioned.h"
#include "types.h"

namespace gameEngine{
	void Positioned::onPositionChange() {}

	Positioned::Positioned() {}

	Positioned::Positioned(Pointf position) {
		setPosition(position.x, position.y);
	}

	Positioned::Positioned(float x, float y) {
		setPosition(x, y);
	}

	Pointf Positioned::getPosition() {
		return position;
	}

	float Positioned::getPositionX()
	{
		return position.x;
	}

	float Positioned::getPositionY()
	{
		return position.y;
	}

	void Positioned::setPosition(Pointf position) {
		setPosition(position.x, position.y);
	}

	void Positioned::setPosition(float x, float y) {
		if (position.x == x && position.y == y) return;

		position.x = x, position.y = y;
		onPositionChange();
	}

	void Positioned::setPositionX(float x) {
		if (position.x == x) return;

		position.x = x;
		onPositionChange();
	}

	void Positioned::setPositionY(float y) {
		if (position.y = y) return;

		position.y = y;
		onPositionChange();
	}

	void Positioned::move(Dimensionf distance) {
		move(distance.width, distance.height);
	}

	void Positioned::move(float dx, float dy) {
		if (dx == 0 && dy == 0) return;

		position.x += dx, position.y += dy;
		onPositionChange();
	}

	void Positioned::moveX(float dx) {
		if (dx == 0) return;

		position.x += dx;
		onPositionChange();
	}

	void Positioned::moveY(float dy) {
		if (dy == 0) return;

		position.y += dy;
		onPositionChange();
	}
}