#pragma once
#include "types.h"

namespace gameEngine {
	class Texture {
		private:
			bool flipped = false;
			virtual void drawNormal(Pointf origin, Dimensionf scaleSize) = 0;
			virtual void drawFlipped(Pointf origin, Dimensionf scaleSize);
		public:
			void draw(Pointf origin, Dimensionf scaleSize);
			bool isFlipped();
			void setFlipped(bool f);
			void flip();
			virtual void update(double delta);
	};
}