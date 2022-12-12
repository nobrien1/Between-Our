#include "uiHeader.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../types.h"
#include "../Positioned.h"
#include "../Sized.h"
#include <functional>
#include <string>
#include "../World.h"
#include "../Camera.h"
#include <iostream>

namespace gameEngine {
	namespace ui {
		GameScreen::GameScreen(World* world, Camera* camera) {
			this->world = world, this->camera = camera;
		}
		void GameScreen::setWorld(World* world) {
			this->world = world;
		}
		void GameScreen::setCamera(Camera* camera) {
			this->camera = camera;
		}
		void GameScreen::render(GLFWwindow* window) {
			camera->renderFrame(window, world);

			for (int i = 0; i < childCount; i++) {
				if (!children[i]->isVisible()) return;

				children[i]->render(window);
			}
		}
		bool GameScreen::attemptRender(GLFWwindow* window) {
			render(window);
			return true;
		}
	}
}