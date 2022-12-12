#pragma once

#include "types.h"

namespace gameEngine {
	class Positioned {
		protected:
			Pointf position;
			virtual void onPositionChange();
		public:
			Positioned();
			Positioned(Pointf position);
			Positioned(float x, float y);
			Pointf getPosition();
			float getPositionX();
			float getPositionY();
			void setPosition(Pointf position);
			void setPosition(float x, float y);
			void setPositionX(float x);
			void setPositionY(float y);
			void move(Dimensionf distance);
			void move(float dx, float dy);
			void moveX(float dx);
			void moveY(float dy);
	};
}

