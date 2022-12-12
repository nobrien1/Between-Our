#include "Polygon.h"
#include "types.h"

gameEngine::Polygon::Polygon()
{
}

gameEngine::Polygon::Polygon(Color3f color)
{
	setColor(color);
}

gameEngine::Polygon::Polygon(Pointf position, Color3f color) : Positioned(position)
{
	setColor(color);
}

gameEngine::Color3f gameEngine::Polygon::getColor()
{
	return color;
}

void gameEngine::Polygon::setColor(Color3f c)
{
	color = c;
}

void gameEngine::Polygon::drawFlipped(Pointf origin, Dimensionf scale)
{
	drawNormal(origin, scale);
}
