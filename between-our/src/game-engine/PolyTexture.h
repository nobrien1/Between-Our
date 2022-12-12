#pragma once
#include "Texture.h"
#include "Polygon.h"
#include "types.h"
namespace gameEngine {
	class PolyTexture : public Texture {
		private:
			Polygon** polys = new Polygon*[0];
			int polyCount = 0;
			Dimensionf size;
			void drawNormal(Pointf origin, Dimensionf scaleSize);
			void drawFlipped(Pointf origin, Dimensionf scaleSize);
		public:
			void addPoly(Polygon* p);
	};
}

