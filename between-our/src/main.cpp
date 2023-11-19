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
#include <future> 
#include <mutex> 
#include <chrono> 
#include "SerialPort.h"

using namespace gameEngine::ui;
using namespace gameEngine;

char comPort[] = "COM5";
char* port = comPort;
SerialPort mySerial(port, CBR_115200);

TextInput nameInput(Pointf(-1920 / 4 + 30, 1080 / 4 - 50), "Enter name");
const char* nameInputVal = " ";
Button goButton(Pointf(-50, 0), Dimensionf(100, 50));
Text goText(Pointf(10, 10), "Start");

Screen initialScreen;

Camera camera;
int following = 1;

World world(500, 500);

Player p1("");
#define NUM_POINTS 90
WorldObject points[NUM_POINTS];

GameScreen screen(&world, &camera);

Text canKill(Pointf(-1920/4 + 30, 1080/4 - 40), "Kill (f)");

PolarPointf toPolarPointf(float x, float y) {
	float r = sqrt(x * x + y * y);
	float theta = atan(y / x);
	if (x < 0) theta += 180;
	return PolarPointf(r, theta);
}

PolarPointf toPolarPointf(Pointf p) {
	return toPolarPointf(p.x, p.y);
}

Pointf toPointf(float r, float theta) {
	float x = r * cos(theta * 3.14 / 180);
	float y = r * sin(theta * 3.14 / 180);
	return Pointf(x, y);
}

Pointf toPointf(PolarPointf p) {
	return toPointf(p.r, p.theta);
}

void readSerial() {
	if (!mySerial.isConnected() || !mySerial.isAvailable()) return;

	char* buffer = mySerial.read();

	if (buffer == nullptr) return;

	unsigned char b = buffer[0];
	if (b != 0xfa) return;

	unsigned char data[4];
	int i = 1;
	data[0] = b;

	while (i < 4) {
		if (!mySerial.isAvailable()) continue;
		char* temp = mySerial.read();
		if (temp == nullptr) return;
		data[i] = temp[0] + 256;
		i++;
	}

	int index = int(data[1]) - 0xa0;
	int mmDist = data[2] + ((data[3] & 0x1f) << 8) / 120;
	std::cout << mmDist << std::endl;

	PolarPointf polar(mmDist, index * 4);
	Pointf p = toPointf(polar);
	points[index].setPosition(p);
}

// 1010
// 0110
// 
// 0010

// 0000 0000
// 0001 1111

void loopSerial() {
	while (true) {
		readSerial();
	}
}

int main() {
	ViewStyle btnStyle;
	btnStyle.bgColor = Color3f(0, 0, 1);
	goButton.setStyle(btnStyle);
	goButton.addUiElement(&goText);
	goButton.setOnPress([](int button, bool action) -> void {
		p1.setName(nameInputVal);
		window::navigate(&screen);

		window::setRenderCallback([](double delta) -> void {
			//readSerial();
			world.gameTick(delta);
			camera.gameTick(delta);

			

			/*if (p1.isInRange(&p2) && !p2.isDead()) {
				canKill.setVisible(true);
			}
			else {
				canKill.setVisible(false);
			}*/
		});
	});

	/*nameInput.setOnChangeText([](char* text) -> void {
		nameInputVal = text;
		});*/

	initialScreen.addUiElement(&goButton);
	//initialScreen.addUiElement(&nameInput);

	//p2.setPlayerColor(BLUE);

	world.addWorldObject(&p1);
	//world.addWorldObject(&p2);

	ColorSquare pointTexture(Color3f(1, 1, 1));

	for (int i = 0; i < NUM_POINTS; i++) {
		PolarPointf polar(90, i * 4);
		Pointf p = toPointf(polar);
		points[i].setPosition(p);
		points[i].setSize(2, 2);
		points[i].setTexture(&pointTexture);
		world.addWorldObject(&(points[i]));
	}

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
		// p2.setMovingUp(action);
		});
	screen.setKeyPress(GLFW_KEY_LEFT, [](bool action) -> void {
		// p2.setMovingLeft(action);
		});
	screen.setKeyPress(GLFW_KEY_DOWN, [](bool action) -> void {
		// p2.setMovingDown(action);
		});
	screen.setKeyPress(GLFW_KEY_RIGHT, [](bool action) -> void {
		// p2.setMovingRight(action);
		});

	screen.setKeyPress(GLFW_KEY_SPACE, [](bool action) -> void {
		/*if (!action) return;

		if (following == 1) {
			following = 2;
			camera.follow(&p2);
		}
		else {
			following = 1;
			camera.follow(&p1);
		}*/
		});

	screen.setKeyPress(GLFW_KEY_F, [](bool action) -> void {
		//if (p1.isInRange(&p2)) p1.attemptToKill(&p2);
		});


	window::navigate(&initialScreen);

	//window::startWindow(1920/2, 1080/2);

	std::future<void> thread0 = std::async(std::launch::async, window::startWindow, 1920 / 2, 1080 / 2);
	std::future<void> thread1 = std::async(std::launch::async, loopSerial);

	return 0;
}