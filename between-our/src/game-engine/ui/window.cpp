#include "uiHeader.h"
#include "textGenerator.h"
#include <iostream>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

namespace gameEngine {
	namespace window {
		GLFWwindow* window;
		bool keysPressed[350];
		Dimensioni windowSize(1920 / 2, 1080 / 2);
		ui::Screen* screen;
		Pointf mouse;
		function<void(double delta)> renderCallback = [](double delta) -> void {};
		bool textInputFocused = false;
		ui::TextInput* focused = new ui::TextInput();

		void resize(GLFWwindow* window, int w, int h) {
			if (h < 1)
				h = 1;
			windowSize.width = w, windowSize.height = h;
			glViewport(0, 0, w, h);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//gluPerspective(45.0f, (double)w / (double)h, 0.1f, 1000.0f);
			//gluLookAt(0.0f, 0.0f, 30, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
			glMatrixMode(GL_MODELVIEW);
		}

		void initialize(void) {
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glClearColor(0.0, 0.0, 0.0, 1.0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		//static void update(GLFWwindow* window, float delta) {
		//	//std::cout << "delta:" << delta << std::endl;
		//	if (keyArr[GLFW_KEY_ESCAPE])
		//		glfwSetWindowShouldClose(window, 1);
		//}

		void renderFrame(GLFWwindow* window) {
			bool reRendered = false;
			reRendered = screen->attemptRender(window);
			if(reRendered) glfwSwapBuffers(window);
		}

		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (textInputFocused) {
				if (action == 0) return;

				bool caps = (mods == GLFW_MOD_SHIFT) != (mods == GLFW_MOD_CAPS_LOCK);

				if (key == GLFW_KEY_ENTER) unfocusTextInput;
				else if (key == GLFW_KEY_BACKSPACE) focused->backspace();
				else if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9 && !caps) focused->addChar((char)key);
				else if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) focused->addChar((char)(key + !caps * 32));
				else if (key == GLFW_KEY_SPACE) focused->addChar(' ');

				return;
			}

			if (action != 0 && action != 1) return;

			bool actionBool = action == 1;
			keysPressed[key] = actionBool;
			screen->getKeyBinds()[key].pressCallback(actionBool);
		}

		void callKeyBinds(double delta) {
			if (focused) return;

			for (int i = 0; i < 350; i++) {
				if (keysPressed[i]) screen->getKeyBinds()[i].bindingCallback(delta);
			}
		}

		static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
			if (textInputFocused && button == GLFW_MOUSE_BUTTON_LEFT && action == 1) unfocusTextInput();

			screen->onClick(button, action > 0, mouse);
		}

		static void mouseMotionCallback(GLFWwindow* window, double x, double y) {
			Pointf mousePos(x - windowSize.width / 2, windowSize.height / 2 - y);
			mouse = mousePos;
			screen->updateMousePosition(mousePos);
		}

		void startWindow(int width, int height) {
			glfwInit();
			window = glfwCreateWindow(width, height, "Between Our", NULL, NULL);
			glfwMakeContextCurrent(window);

			windowSize.width = width, windowSize.height = height;

			initialize();
			glfwSetWindowSizeCallback(window, resize);
			glfwSetKeyCallback(window, keyCallback);
			glfwSetMouseButtonCallback(window, mouseClickCallback);
			glfwSetCursorPosCallback(window, mouseMotionCallback);

			while (!glfwWindowShouldClose(window)) {
				double delta = glfwGetTime();

				glfwSetTime(0);
				
				callKeyBinds(delta);
				renderCallback(delta);
				renderFrame(window);

				glfwPollEvents();
			}
			glfwDestroyWindow(window);
		}

		void setRenderCallback(std::function<void(double delta)> callback) {
			renderCallback = callback;
		}

		void setCursor(int shape) {
			GLFWcursor* cursor = glfwCreateStandardCursor(shape);
			glfwSetCursor(window, cursor);
		}

		void navigate(ui::Screen* s) {
			screen = s;
		}

		void focusTextInput(ui::TextInput* input)
		{
			textInputFocused = true;
			focused = input;
			input->focus();
		}

		void unfocusTextInput()
		{
			textInputFocused = false;
			focused->unfocus();
			focused = new ui::TextInput();
		}

		Pointf toDrawablePoint(Pointf p) {
			const float x = p.x / ((float) windowSize.width / 2);
			const float y = p.y / ((float) windowSize.height / 2);
			return Pointf(x, y);
		}

		Dimensioni getWindowSize() {
			return windowSize;
		}

		int getLeftBound() {
			return -windowSize.width / 2;
		}

		int getRightBound() {
			return windowSize.width / 2;
		}

		int getTopBound() {
			return windowSize.height / 2;
		}

		int getBottomBound() {
			return -windowSize.height / 2;
		}

		void clear(Color3f color) {
			glfwMakeContextCurrent(window);
			glClearColor(color.r, color.g, color.b, 1);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void drawRect(Pointf p, Dimensionf size, Color3f color, float bgOpacity) {
			glfwMakeContextCurrent(window);

			Pointf newTL = toDrawablePoint(p);
			Pointf newBR = toDrawablePoint(Pointf(p.x + size.width, p.y + size.height));

			glColor4f(color.r, color.g, color.b, bgOpacity);
			glBegin(GL_QUADS);
			glVertex2f(newTL.x, newTL.y);
			glVertex2f(newBR.x, newTL.y);
			glVertex2f(newBR.x, newBR.y);
			glVertex2f(newTL.x, newBR.y);
			glEnd();
			glFlush();
		}

		void drawRect(Pointf p, Dimensionf size, Color3f color) {
			drawRect(p, size, color, 1);
		}

		void drawRectOutline(Pointf p, Dimensionf size, Color3f color, float borderWidth) {
			glfwMakeContextCurrent(window);

			Pointf newTL = toDrawablePoint(p);
			Pointf newBR = toDrawablePoint(Pointf(p.x + size.width, p.y + size.height));

			glColor3f(color.r, color.g, color.b);
			glLineWidth(borderWidth);
			glBegin(GL_LINE_LOOP);
			glVertex2f(newTL.x, newTL.y);
			glVertex2f(newBR.x, newTL.y);
			glVertex2f(newBR.x, newBR.y);
			glVertex2f(newTL.x, newBR.y);
			glEnd();
			glFlush();
		}

		void drawTextImage(Pointf p, text::TextImage image, Color3f color) {
			const float xPixelSize = 1.0f / windowSize.width;
			const float yPixelSize = 1.0f / windowSize.height;

			glBegin(GL_POINTS);

			for (int i = 0; i < image.size.height; i++) {
				for (int j = 0; j < image.size.width; j++) {
					float a = (float)image.buffer[i][j] / 256;
					if (a == 0) continue;

					Pointf pixel;
					pixel = toDrawablePoint(Pointf(j + p.x, -i + p.y + image.size.height));

					glColor4f(color.r, color.g, color.b, a);
					glVertex2f(pixel.x, pixel.y);
				}
			}
			glEnd();
			glFlush();
		}
	}
}