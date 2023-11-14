#include "types.h"
#include <math.h>

namespace gameEngine {
	/*template<typename T> Point<T>::Point() {
		x = 0, y = 0;
	}

	template<typename T> Point<T>::Point(T x, T y) {
		this->x = x, this->y = y;
	}*/

	Pointf::Pointf() {
		x = 0, y = 0;
	}

	Pointf::Pointf(float x, float y) {
		this->x = x, this->y = y;
	}

	PolarPointf::PolarPointf() {
		r = 0, theta = 0;
	}

	PolarPointf::PolarPointf(float r, float theta) {
		this->r = r, this->theta = theta;
	}

	Dimensionf::Dimensionf() {
		width = 0, height = 0;
	}

	Dimensionf::Dimensionf(float width, float height) {
		this->width = width, this->height = height;
	}

	Dimensioni::Dimensioni() {
		width = 0, height = 0;
	}

	Dimensioni::Dimensioni(int width, int height) {
		this->width = width, this->height = height;
	}

	Vectorf::Vectorf() {
		x = 0, y = 0;
	}

	Vectorf::Vectorf(float x, float y) {
		this->x = x, this->y = y;
	}

	Color3f::Color3f() {
		r = 0, g = 0, b = 0;
	}

	Color3f::Color3f(float r, float g, float b) {
		this->r = r, this->g = g, this->b = b;
	}
	BoundingBox::BoundingBox()
	{
		left = 0, right = 0, top = 0, bottom = 0;
	}
	BoundingBox::BoundingBox(float left, float right, float top, float bottom)
	{
		this->left = left, this->right = right, this->top = top, this->bottom = bottom;
	}
	BoundingBox::BoundingBox(Pointf origin, Dimensionf size)
	{
		left = origin.x;
		right = origin.x + size.width;
		top = origin.y + size.height;
		bottom = origin.y;
	}
}

