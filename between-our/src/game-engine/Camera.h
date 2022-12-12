#pragma once
#include "types.h"
#include "World.h"
#include "Positioned.h"
#include "Texturable.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gameEngine {
	class Camera : public Positioned, public Texturable {
		private:
			Dimensioni windowSize;
			void drawRect(Pointf topLeft, Dimensionf size, Color3f color);
			Pointf transformPoint(Pointf p);
			Positioned* toFollow = NULL;
			float followSpeed = 10.0f;
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
	};
};