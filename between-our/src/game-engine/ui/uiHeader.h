#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../types.h"
#include "../Positioned.h"
#include "../Sized.h"
#include <functional>
#include <string>
#include "../World.h"
#include "../Camera.h"
#include "textGenerator.h"

namespace gameEngine {
	namespace ui {
		using KeyBindingCallback = std::function<void(double delta)>;
		using KeyPressCallback = std::function<void(bool action)>;

		struct KeyBind {
			KeyBindingCallback bindingCallback = [](double delta) -> void {};
			KeyPressCallback pressCallback = [](bool action) -> void {};
		};

		class UiElement : public Positioned {
			protected:
				bool reRenderQueued = true;
				bool mouseInside = false;
				bool visible = true;
				void onPositionChange();
			public:
				UiElement();
				UiElement(float x, float y);
				UiElement(Pointf position);
				virtual void render(GLFWwindow* window, float offsetX, float offsetY);
				void render(GLFWwindow* window, Dimensionf offset);
				void render(GLFWwindow* window);
				bool isReRenderQueued();
				void forceReRender();
				virtual bool isInside(Pointf p);
				bool isMouseInside();
				virtual void onMouseEnter();
				virtual void onMouseExit();
				virtual void onClick(int button, bool action);
				bool isVisible();
				void setVisible(bool v);
		};

		class Nestable {
			protected:
				UiElement** children = {};
				int childCount = 0;
			public:
				void addUiElement(UiElement* element);
				void addUiElement(UiElement* element, int zIndex);
		};

		struct Style {
			Color3f bgColor;
		};

		using OnPress = std::function<void(int button, bool action)>;

		class Screen : public Nestable {
			protected:
				Style style;
				KeyBind keyBinds[350];
				Dimensioni windowSize;
				bool reRenderQueued = true;
			public:
				Screen();
				Screen(Style style);
				virtual void render(GLFWwindow* window);
				virtual bool attemptRender(GLFWwindow* window);
				void updateMousePosition(Pointf p);
				void onClick(int button, bool action, Pointf p);
				void setKeyBind(int key, KeyBindingCallback callback);
				void setKeyPress(int key, KeyPressCallback callback);
				KeyBind* getKeyBinds();
				void setWindowSize(Dimensioni s);
				void setWindowSize(int width, int height);
				void setStyle(Style style);
		};

		struct ViewStyle : public Style {
			float borderWidth = 0;
			Color3f borderColor;
			bool bgVisible = true;
		};

		class View : public UiElement, public Nestable, public Sized {
			protected:
				ViewStyle style;
				void onSizeChange();
			public:
				View();
				View(Pointf position, Dimensionf size);
				View(Pointf position, Dimensionf size, ViewStyle style);
				ViewStyle getStyle();
				void setStyle(ViewStyle style);
				void render(GLFWwindow* window, float offsetX, float offsetY);
				bool isReRenderQueued();
				bool isInside(Pointf p);
				void onMouseEnter();
				void onMouseExit();
		};

		struct TextStyle : public ViewStyle {
			Color3f fontColor = Color3f(0.5, 0.5, 0.5);
			int fontSize = 15;
			bool bgVisible = false;
		};

		class Text : public UiElement {
			protected:
				char* text;
				text::TextImage image;
				TextStyle style;
				void updateImage();
			public:
				Text(char* text);
				Text(Pointf position, char* text);
				Text(Pointf position, char* text, TextStyle style);
				Text(Pointf position, std::string text);
				Text(Pointf position, std::string text, TextStyle style);
				char* getText();
				void setText(char* text);
				void setText(std::string text);
				void setStyle(TextStyle style);
				Dimensioni getSize();
				void render(GLFWwindow* window, float offsetX, float offsetY);
				bool isInside(Pointf p);
				void onMouseEnter();
				void onMouseExit();
		};

		using ChangeTextCallback = std::function<void(char* text)>;

		class TextInput : public Text {
			private:
				std::string value = "";
				std::string placeholder;
				ChangeTextCallback onChangeText = [](char* text) -> void {};
				TextStyle normalStyle, placeholderStyle;
				void showPlaceholder();
				void hidePlaceholder();
			public:
				TextInput();
				TextInput(Pointf position);
				TextInput(Pointf position, char* placeholder);
				TextInput(Pointf position, std::string placeholder);
				TextInput(Pointf position, char* placeholder, TextStyle style);
				TextInput(Pointf position, std::string placeholder, TextStyle style);
				char* getPlaceholder();
				void setPlaceholder(std::string p);
				void setOnChangeText(ChangeTextCallback callback);
				void onClick(int button, bool action);
				void addChar(char c);
				void backspace();
				void onMouseEnter();
				void onMouseExit();
				void focus();
				void unfocus();
		};

		class Button : public View {
			private:
				OnPress onPress = [](int button, bool action) -> void {};
				ViewStyle mouseOffStyle, mouseOnStyle;
			public:
				Button();
				Button(Pointf position, Dimensionf size);
				Button(Pointf position, Dimensionf size, ViewStyle style);
				Button(Pointf position, Dimensionf size, ViewStyle style, OnPress onPress);
				OnPress getOnPress();
				void setOnPress(OnPress onPress);
				void onClick(int button, bool action);
				void onMouseEnter();
				void onMouseExit();
		};

		class GameScreen : public Screen {
			private:
				World* world;
				Camera* camera;
			public:
				GameScreen(World* world, Camera* camera);
				void setWorld(World* world);
				void setCamera(Camera* camera);
				void render(GLFWwindow* window);
				bool attemptRender(GLFWwindow* window);
		};
	}

	namespace window {
		void startWindow(int width, int height);
		void setRenderCallback(std::function<void(double delta)> callback);
		void setCursor(int shape);
		void navigate(ui::Screen* s);
		void focusTextInput(ui::TextInput* input);
		void unfocusTextInput();
		Pointf toDrawablePoint(Pointf p);
		Dimensioni getWindowSize();
		int getLeftBound();
		int getRightBound();
		int getTopBound();
		int getBottomBound();
		void clear(Color3f color);
		void drawRect(Pointf p, Dimensionf size, Color3f color);
		void drawRect(Pointf p, Dimensionf size, Color3f color, float bgOpacity);
		void drawRectOutline(Pointf p, Dimensionf size, Color3f color, float borderWidth);
		void drawTextImage(Pointf p, text::TextImage image, Color3f color);
	}
}