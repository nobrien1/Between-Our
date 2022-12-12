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
		void View::onSizeChange()
		{
			forceReRender();
		}
		View::View() {}
		View::View(Pointf position, Dimensionf size) : UiElement(position), Sized(size) {}
		View::View(Pointf position, Dimensionf size, ViewStyle style) : UiElement(position), Sized(size) {
			this->style = style;
		}

		ViewStyle View::getStyle() {
			return style;
		}

		void View::setStyle(ViewStyle style) {
			this->style = style;
			forceReRender();
		}

		void View::render(GLFWwindow* window, float offsetX, float offsetY) {
			Pointf origin = Pointf(position.x + offsetX, position.y + offsetY);

			if(style.bgVisible) gameEngine::window::drawRect(origin, size, style.bgColor);
			if (style.borderWidth > 0) 
				gameEngine::window::drawRectOutline(origin, size, style.borderColor, style.borderWidth);

			for (int i = 0; i < childCount; i++) {
				children[i]->render(window, origin.x, origin.y);
			}

			reRenderQueued = false;
		}

		bool View::isReRenderQueued() {
			if (reRenderQueued) return true;

			for (int i = 0; i < childCount; i++) {
				if (children[i]->isReRenderQueued()) return true;
			}

			return false;
		}

		bool View::isInside(Pointf p) {
			return p.x > position.x && p.y > position.y && p.x < position.x + size.width && p.y < position.y + size.height;
		}

		void View::onMouseEnter() {
			mouseInside = true;
		}

		void View::onMouseExit() {
			mouseInside = false;
		}
	}
}