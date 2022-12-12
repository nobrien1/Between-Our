#include "uiHeader.h"
#include "../types.h"
#include <string>
#include <functional>
#include <iostream>
#include <string>

namespace gameEngine {
	namespace ui {
		void TextInput::showPlaceholder()
		{
			setStyle(placeholderStyle);
			setText(placeholder);
		}
		void TextInput::hidePlaceholder()
		{
			setStyle(normalStyle);
			setText(value);
		}
		TextInput::TextInput() : Text(new char[0]) {
			placeholderStyle.fontColor = Color3f(0.25, 0.25, 0.25);
		}
		TextInput::TextInput(Pointf position) : Text(position, new char[0]) {
			placeholderStyle.fontColor = Color3f(0.25, 0.25, 0.25);
		}
		
		TextInput::TextInput(Pointf position, char* placeholder) : Text(position, new char[0]) {
			placeholderStyle.fontColor = Color3f(0.25, 0.25, 0.25);
			setPlaceholder(placeholder);
		}
		
		TextInput::TextInput(Pointf position, std::string placeholder) : Text(position, new char[0]) {
			placeholderStyle.fontColor = Color3f(0.25, 0.25, 0.25);
			setPlaceholder(placeholder);
		}
		TextInput::TextInput(Pointf position, char* placeholder, TextStyle style) : Text(position, new char[0]) {
			this->style = style;
			placeholderStyle.fontColor = Color3f(style.fontColor.r / 2, style.fontColor.g / 2, style.fontColor.b / 2);
			setPlaceholder(placeholder);
		}
		TextInput::TextInput(Pointf position, std::string placeholder, TextStyle style) : Text(position, new char[0]) {
			this->style = style;
			placeholderStyle.fontColor = Color3f(style.fontColor.r / 2, style.fontColor.g / 2, style.fontColor.b / 2);
			setPlaceholder(placeholder);
		}
		char* TextInput::getPlaceholder() {
			return &placeholder[0];
		}
		void TextInput::setPlaceholder(std::string p) {
			placeholder = p;
			if (value.length() <= 0) showPlaceholder();
		}
		void TextInput::setOnChangeText(ChangeTextCallback callback) {
			this->onChangeText = callback;
		}
		void TextInput::onClick(int button, bool action) {
			if(button == GLFW_MOUSE_BUTTON_LEFT && action == 1) window::focusTextInput(this);
		}
		void TextInput::addChar(char c)
		{
			value += c;

			setText(value + '_');
			onChangeText(&value[0]);
		}
		void TextInput::backspace()
		{
			if (value.length() <= 0) return;

			value = value.substr(0, value.length() - 1);

			setText(value + '_');
			onChangeText(&value[0]);
		}
		void TextInput::onMouseEnter()
		{
			Text::onMouseEnter();
			window::setCursor(GLFW_IBEAM_CURSOR);
		}
		void TextInput::onMouseExit()
		{
			Text::onMouseExit();
			window::setCursor(GLFW_ARROW_CURSOR);
		}
		void TextInput::focus()
		{
			hidePlaceholder();
			setText(value + '_');
		}
		void TextInput::unfocus()
		{
			if (value.length() <= 0) {
				showPlaceholder();
			}
			else {
				hidePlaceholder();
				setText(value);
			}
		}
	}
}