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
#include "textGenerator.h"

namespace gameEngine {
	namespace ui {
		void Text::updateImage() {
			image = gameEngine::text::getTextImage(text, style.fontSize);
			forceReRender();
		}

		Text::Text(char* text) {
			setText(text);
		}

		Text::Text(Pointf position, char* text) : UiElement(position) {
			setText(text);
		}

		Text::Text(Pointf position, char* text, TextStyle style) : UiElement(position) {
			setText(text);
			this->style = style;
		}

		Text::Text(Pointf position, std::string text) : UiElement(position) {
			setText(&text[0]);
		}

		Text::Text(Pointf position, std::string text, TextStyle style) : UiElement(position) {
			setText(&text[0]);
			this->style = style;
		}

		char* Text::getText() {
			return text;
		}

		void Text::setText(char* text) {
			this->text = text;
			updateImage();
		}

		void Text::setText(std::string text) {
			setText(&text[0]);
		}

		void Text::setStyle(TextStyle style) {
			this->style = style;
			updateImage();
		}

		Dimensioni Text::getSize() {
			return image.size;
		}

		void Text::render(GLFWwindow* window, float offsetX, float offsetY) {
			Pointf origin = Pointf(position.x + offsetX, position.y + offsetY);
			Dimensionf sizef = Dimensionf(image.size.width, image.size.height);

			if (style.bgVisible) gameEngine::window::drawRect(origin, sizef, style.bgColor);
			if (style.borderWidth > 0)
				gameEngine::window::drawRectOutline(origin, sizef, style.borderColor, style.borderWidth);

			gameEngine::window::drawTextImage(origin, image, style.fontColor);

			reRenderQueued = false;
		}
		bool Text::isInside(Pointf p)
		{
			BoundingBox b = BoundingBox(position, Dimensionf(image.size.width, image.size.height));
			return p.x > b.left && p.x < b.right&& p.y > b.bottom && p.y < b.top;
		}
		void Text::onMouseEnter()
		{
			mouseInside = true;
		}
		void Text::onMouseExit()
		{
			mouseInside = false;
		}
	}
}