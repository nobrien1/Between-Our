#include "Texturable.h"
#include "types.h"
#include "ColorSquare.h"

namespace gameEngine {
	Texturable::Texturable()
	{
	}
	Texturable::Texturable(Texture* texture)
	{
		setTexture(texture);
	}
	Texture* Texturable::getTexture()
	{
		return texture;
	}
	void Texturable::setTexture(Texture* t)
	{
		texture = t;
	}
}