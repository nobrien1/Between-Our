#pragma once
#include "types.h"
#include "World.h"
#include "Positioned.h"
#include "Texturable.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define ZOOM_SPEED 1

namespace gameEngine {
	class Camera : public Positioned, public Texturable {
		private:
			Dimensioni windowSize;
			Pointf transformPoint(Pointf p);
			Dimensionf transformDimension(Dimensionf d);
			Positioned* toFollow = NULL;
			float followSpeed = 10.0;
			float scale = 1.0;
			bool zoomingIn = false;
			bool zoomingOut = false;
		public:
			Camera();
			Dimensioni getWindowSize();
			void setWindowSize(Dimensioni size);
			void setWindowSize(int width, int height);
			void renderFrame(GLFWwindow* window, World* world);
			void gameTick(double delta);
			void follow(Positioned* p);
			float getFollowSpeed();
			void setFollowSpeed(float f);
			void setScale(float s);
			float getScale();
			void setZoomingIn(bool z);
			void setZoomingOut(bool z);
	};
};