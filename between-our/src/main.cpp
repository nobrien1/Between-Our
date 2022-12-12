#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "game-engine/types.h"
#include "game-engine/WorldObject.h";
#include "game-engine/World.h"
#include "game-engine/Camera.h"
#include "game-engine/Player.h"
#include "game-engine/ui/uiHeader.h"
#include <string>

using namespace gameEngine::ui;
using namespace gameEngine;

TextInput nameInput(Pointf(-1920 / 4 + 30, 1080 / 4 - 50), "Enter name");
char* nameInputVal = {};
Button goButton(Pointf(-50, 0), Dimensionf(100, 50));
Text goText(Pointf(10, 10), "Start");

Screen initialScreen;

Camera camera;
int following = 1;

World world(500, 500);

Player p1("");

Player p2("Player 2");

GameScreen screen(&world, &camera);

Text canKill(Pointf(-1920/4 + 30, 1080/4 - 40), "Kill (f)");

int main() {
	ViewStyle btnStyle;
	btnStyle.bgColor = Color3f(0, 0, 1);
	goButton.setStyle(btnStyle);
	goButton.addUiElement(&goText);
	goButton.setOnPress([](int button, bool action) -> void {
		p1.setName(nameInputVal);
		window::navigate(&screen);
		window::setRenderCallback([](double delta) -> void {
			world.gameTick(delta);
			camera.gameTick(delta);

			if (p1.isInRange(&p2) && !p2.isDead()) {
				canKill.setVisible(true);
			}
			else {
				canKill.setVisible(false);
			}
		});
	});

	nameInput.setOnChangeText([](char* text) -> void {
		nameInputVal = text;
		});

	initialScreen.addUiElement(&goButton);
	initialScreen.addUiElement(&nameInput);

	p2.setPlayerColor(BLUE);

	world.addWorldObject(&p1);
	world.addWorldObject(&p2);

	camera.follow(&p1);

	screen.setKeyPress(GLFW_KEY_W, [](bool action) -> void {
		p1.setMovingUp(action);
	});
	screen.setKeyPress(GLFW_KEY_A, [](bool action) -> void {
		p1.setMovingLeft(action);
	});
	screen.setKeyPress(GLFW_KEY_S, [](bool action) -> void {
		p1.setMovingDown(action);
	});
	screen.setKeyPress(GLFW_KEY_D, [](bool action) -> void {
		p1.setMovingRight(action);
	});

	screen.setKeyPress(GLFW_KEY_UP, [](bool action) -> void {
		p2.setMovingUp(action);
		});
	screen.setKeyPress(GLFW_KEY_LEFT, [](bool action) -> void {
		p2.setMovingLeft(action);
		});
	screen.setKeyPress(GLFW_KEY_DOWN, [](bool action) -> void {
		p2.setMovingDown(action);
		});
	screen.setKeyPress(GLFW_KEY_RIGHT, [](bool action) -> void {
		p2.setMovingRight(action);
		});

	screen.setKeyPress(GLFW_KEY_SPACE, [](bool action) -> void {
		if (!action) return;

		if (following == 1) {
			following = 2;
			camera.follow(&p2);
		}
		else {
			following = 1;
			camera.follow(&p1);
		}
		});

	screen.setKeyPress(GLFW_KEY_F, [](bool action) -> void {
		if (p1.isInRange(&p2)) p1.attemptToKill(&p2);
		});

	
	screen.addUiElement(&canKill);

	window::navigate(&initialScreen);

	window::startWindow(1920/2, 1080/2);

	return 0;
}