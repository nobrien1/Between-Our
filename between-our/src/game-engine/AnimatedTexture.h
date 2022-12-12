#pragma once
#include "Texture.h"

namespace gameEngine {
	class AnimatedTexture : public Texture {
		private:
			Texture** frames = new Texture * [0];
			int frameCount = 0;
			float fps = 3;
			int currentFrame = 0;
			float currentTime = 0;
			void drawNormal(Pointf origin, Dimensionf scaleSize);
			void drawFlipped(Pointf origin, Dimensionf scaleSize);
		public:
			void addFrame(Texture* frame);
			float getFps();
			void setFps(float fps);
			void update(double delta);
	};
}

