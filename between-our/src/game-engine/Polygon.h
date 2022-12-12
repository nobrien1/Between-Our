#pragma once

#include "types.h"
#include "Positioned.h"

namespace gameEngine {
	class Polygon : public Positioned {
		private:
			Color3f color;
		public:
			Polygon();
			Polygon(Color3f color);
			Polygon(Pointf position, Color3f color);
			Color3f getColor();
			void setColor(Color3f c);
			virtual void drawNormal(Pointf origin, Dimensionf scale) = 0;
			virtual void drawFlipped(Pointf origin, Dimensionf scale);
			virtual float getWidth() = 0;
			virtual float getHeight() = 0;
	};
}


