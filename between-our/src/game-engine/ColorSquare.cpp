#include "ColorSquare.h"
#include "types.h"
#include "ui/uiHeader.h"

void gameEngine::ColorSquare::drawNormal(Pointf origin, Dimensionf scaleSize)
{
	gameEngine::window::drawRect(origin, scaleSize, color);
}

gameEngine::ColorSquare::ColorSquare()
{
}

gameEngine::ColorSquare::ColorSquare(Color3f color)
{
	setColor(color);
}

gameEngine::Color3f gameEngine::ColorSquare::getColor()
{
	return color;
}

void gameEngine::ColorSquare::setColor(Color3f c)
{
	color = c;
}
