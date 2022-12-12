#include "uiHeader.h"
#include "../types.h"
#include "GLFW/glfw3.h"

namespace gameEngine {
	namespace ui {
		void UiElement::onPositionChange()
		{
			forceReRender();
		}
		UiElement::UiElement() {}
		UiElement::UiElement(float x, float y) : Positioned(x, y) {}
		UiElement::UiElement(Pointf position) : Positioned(position) {}

		void UiElement::render(GLFWwindow* window, float offsetX, float offsetY) {}

		void UiElement::render(GLFWwindow* window, Dimensionf offset) {
			render(window, offset.width, offset.height);
		}

		void UiElement::render(GLFWwindow* window) {
			render(window, 0, 0);
		}

		bool UiElement::isReRenderQueued() {
			return reRenderQueued;
		}

		void UiElement::forceReRender() {
			reRenderQueued = true;
		}

		bool UiElement::isInside(Pointf p) {
			return false;
		}

		bool UiElement::isMouseInside() {
			return mouseInside;
		}

		void UiElement::onMouseEnter() {}
		void UiElement::onMouseExit() {}
		void UiElement::onClick(int button, bool action) {}

		bool UiElement::isVisible() {
			return visible;
		}
		void UiElement::setVisible(bool v) {
			visible = v;
			forceReRender();
		}
	}
}