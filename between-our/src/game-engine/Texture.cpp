#include "Texture.h"

void gameEngine::Texture::drawFlipped(Pointf origin, Dimensionf scaleSize)
{
	drawNormal(origin, scaleSize);
}

void gameEngine::Texture::draw(Pointf origin, Dimensionf scaleSize)
{
	if (!flipped)
		drawNormal(origin, scaleSize);
	else
		drawFlipped(origin, scaleSize);
}

bool gameEngine::Texture::isFlipped()
{
	return flipped;
}

void gameEngine::Texture::setFlipped(bool f)
{
	flipped = f;
}

void gameEngine::Texture::flip()
{
	flipped = !flipped;
}

void gameEngine::Texture::update(double delta)
{
}
