#pragma once
#include "types.h"
#include "Texture.h"
#include "ColorSquare.h";

namespace gameEngine {
	class Texturable {
		private:
			Texture* texture = new ColorSquare();
		public:
			Texturable();
			Texturable(Texture* texture);
			Texture* getTexture();
			void setTexture(Texture* t);
	};
}