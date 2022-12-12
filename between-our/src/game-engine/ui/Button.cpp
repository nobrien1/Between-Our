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
		Button::Button() {}

		Button::Button(Pointf position, Dimensionf size) : View(position, size) {}

		Button::Button(Pointf position, Dimensionf size, ViewStyle style) : View(position, size, style) {
			mouseOffStyle = ViewStyle(style);
			mouseOnStyle = style;
			Color3f bgColor;
			bgColor.r = style.bgColor.r * 0.5 + 0.5 * 0.5;
			bgColor.g = style.bgColor.g * 0.5 + 0.5 * 0.5;
			bgColor.b = style.bgColor.b * 0.5 + 0.5 * 0.5;
			mouseOnStyle.bgColor = bgColor;
			mouseOnStyle.borderWidth += 2;
		}
		Button::Button(Pointf position, Dimensionf size, ViewStyle style, OnPress onPress) : View(position, size, style) {
			mouseOffStyle = ViewStyle(style);
			mouseOnStyle = style;
			Color3f bgColor;
			bgColor.r = style.bgColor.r * 0.5 + 0.5 * 0.5;
			bgColor.g = style.bgColor.g * 0.5 + 0.5 * 0.5;
			bgColor.b = style.bgColor.b * 0.5 + 0.5 * 0.5;
			mouseOnStyle.bgColor = bgColor;
			mouseOnStyle.borderWidth += 2;

			this->onPress = onPress;
		}
		OnPress Button::getOnPress() {
			return onPress;
		}
		void Button::setOnPress(OnPress onPress) {
			this->onPress = onPress;
		}
		void Button::onClick(int button, bool action) {
			style = action ? mouseOnStyle : mouseOffStyle;
			forceReRender();
			onPress(button, action);
		}
		void Button::onMouseEnter() {
			View::onMouseEnter();
			window::setCursor(GLFW_HAND_CURSOR);
		}
		void Button::onMouseExit() {
			View::onMouseExit();
			window::setCursor(GLFW_ARROW_CURSOR);
		}
	}
}