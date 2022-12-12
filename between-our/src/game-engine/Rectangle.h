#pragma once
#include "Polygon.h"
#include "Positioned.h"
#include "Sized.h"
#include "types.h"
namespace gameEngine {
	class Rectangle : public Sized, public Polygon {
		public:
			Rectangle(Pointf position, Dimensionf size, Color3f color);
			void drawNormal(Pointf origin, Dimensionf scale);
			void drawFlipped(Pointf origin, Dimensionf scale);
			float getWidth();
			float getHeight();
	};
}


