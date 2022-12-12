#include "PolyTexture.h"
#include "Polygon.h"
#include "types.h"
#include "ui/uiHeader.h"
#include <iostream>

namespace gameEngine {
	void PolyTexture::drawNormal(Pointf origin, Dimensionf scaleSize)
	{
		Dimensionf scale = scaleSize;
		for (int i = 0; i < polyCount; i++)
			polys[i]->drawNormal(origin, scale);
	}
	void PolyTexture::drawFlipped(Pointf origin, Dimensionf scaleSize)
	{
		Dimensionf scale = scaleSize;
		for (int i = 0; i < polyCount; i++) {
			Polygon* poly = polys[i];
			Pointf p = Pointf(origin.x + size.width * scale.width, origin.y);
			poly->drawFlipped(p, scale);
		}
	}
	void PolyTexture::addPoly(Polygon* p)
	{
		Polygon** newList = new Polygon*[polyCount + 1];
		for (int i = 0; i < polyCount; i++)
			newList[i] = polys[i];
		newList[polyCount] = p;
		polys = newList;
		polyCount += 1;

		float widthMax = p->getPositionX() + p->getWidth();
		float heightMax = p->getPositionY() + p->getHeight();
		if (widthMax > size.width) size.width = widthMax;
		if (heightMax > size.height) size.height = heightMax;
	}
}