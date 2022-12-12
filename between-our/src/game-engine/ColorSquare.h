#pragma once

#include "Texture.h"
#include "types.h"

namespace gameEngine {
	class ColorSquare : public Texture {
		private:
			Color3f color;
			void drawNormal(Pointf origin, Dimensionf scaleSize);
		public:
			ColorSquare();
			ColorSquare(Color3f color);
			Color3f getColor();
			void setColor(Color3f c);
	};
}