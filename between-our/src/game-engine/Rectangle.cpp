#include "Rectangle.h"
#include "types.h"
#include "ui/uiHeader.h"

namespace gameEngine {
	Rectangle::Rectangle(Pointf position, Dimensionf size, Color3f color) : Sized(size), Polygon(position, color)
	{
	}
	void Rectangle::drawNormal(Pointf origin, Dimensionf scale)
	{
		Pointf p = Pointf(position.x * scale.width + origin.x, position.y * scale.height + origin.y);
		Dimensionf s = Dimensionf(size.width * scale.width, size.height * scale.height);
		window::drawRect(p, s, getColor());
	}
	void Rectangle::drawFlipped(Pointf origin, Dimensionf scale)
	{
		Pointf p = Pointf(-position.x * scale.width + origin.x, position.y * scale.height + origin.y);
		Dimensionf s = Dimensionf(-size.width * scale.width, size.height * scale.height);
		window::drawRect(p, s, getColor());
	}
	float Rectangle::getWidth()
	{
		return Sized::getWidth();
	}
	float Rectangle::getHeight()
	{
		return Sized::getHeight();
	}
}