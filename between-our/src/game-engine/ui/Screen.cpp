#include "uiHeader.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../types.h"
#include "../Positioned.h"
#include "../Sized.h"
#include <iostream>

namespace gameEngine {
	namespace ui {
		Screen::Screen() {}
		Screen::Screen(Style style) {
			this->style = style;
		}

		void Screen::render(GLFWwindow* window) {
			gameEngine::window::clear(style.bgColor);

			for (int i = 0; i < childCount; i++) {
				if (!children[i]->isVisible()) continue;
					
				children[i]->render(window);
			}

			reRenderQueued = false;
		}

		bool Screen::attemptRender(GLFWwindow* window) {
			if (reRenderQueued) {
				render(window);
				return true;
			}

			for (int i = 0; i < childCount; i++) {
				if (children[i]->isVisible() && children[i]->isReRenderQueued()) {
					render(window);
					return true;
				}
			}
			return false;
		}

		void Screen::updateMousePosition(Pointf p) {
			for (int i = 0; i < childCount; i++) {
				UiElement* e = children[i];
				if (e->isInside(p) && e->isVisible()) {
					if (!e->isMouseInside()) {
						e->onMouseEnter();
					}
				}
				else {
					if (e->isMouseInside()) {
						e->onMouseExit();
					}
				}
			}
		}

		void Screen::onClick(int button, bool action, Pointf p) {
			for (int i = 0; i < childCount; i++) {
				UiElement* e = children[i];
				if (!e->isVisible()) continue;

				if (e->isInside(p)) e->onClick(button, action);
			}
		}

		void Screen::setKeyBind(int key, KeyBindingCallback callback) {
			keyBinds[key].bindingCallback = callback;
		}

		void Screen::setKeyPress(int key, KeyPressCallback callback) {
			keyBinds[key].pressCallback = callback;
		}

		KeyBind* Screen::getKeyBinds() {
			return keyBinds;
		}

		void Screen::setWindowSize(int width, int height) {
			windowSize.width = width, windowSize.height = height;
		}

		void Screen::setWindowSize(Dimensioni s) {
			setWindowSize(s.width, s.height);
		}

		void Screen::setStyle(Style style) {
			this->style = style;
		}
	}
}