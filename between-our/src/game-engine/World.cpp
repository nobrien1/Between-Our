#include "World.h"
#include "Sized.h"
#include "WorldObject.h"
#include "types.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "ColorSquare.h"
#include "types.h"

namespace gameEngine {
	void World::checkCollision()
	{
		for (int i = 0; i < worldObjectCount; i++) {
			WorldObject* w1 = worldObjects[i];
			BoundingBox w1Bounds = w1->getBoundingBox();
			Dimensionf w1Size = w1->getSize();

			if (!w1->shouldCheckCollision()) continue;

			if (w1Bounds.left < 0) w1->setPositionX(0);
			else if (w1Bounds.right > size.width) w1->setPositionX(size.width - w1Size.width);
			if (w1Bounds.bottom < 0) w1->setPositionY(0);
			else if (w1Bounds.top > size.height) w1->setPositionY(size.height - w1Size.height);

			for (int j = 0; j < worldObjectCount; j++) {
				if (i == j) continue;

				WorldObject* w2 = worldObjects[j];
				BoundingBox w2Bounds = w2->getBoundingBox();

				float h1 = w2Bounds.left - w1Bounds.right, h2 = w1Bounds.left - w2Bounds.right;
				float v1 = w2Bounds.bottom - w1Bounds.top, v2 = w1Bounds.bottom - w2Bounds.top;
				
				if (h1 >= 0 || h2 >= 0 || v1 >= 0 || v2 >= 0) continue;

				float moveX = 0, moveY = 0;

				if (h1 >= h2 && h1 >= v1 && h1 >= v2) moveX = h1;
				else if (h2 >= h1 && h2 >= v1 && h2 >= v2) moveX = -h2;
				else if (v1 >= h1 && v1 >= h2 && v1 >= v2) moveY = v1;
				else moveY = -v2;

				if (w2->shouldCheckCollision()) {
					w1->move(moveX / 2, moveY / 2);
					w2->move(-moveX / 2, -moveY / 2);
				}
				else {
					w1->move(moveX, moveY);
				}
			}

			w1->setCheckCollision(false);
		}
	}
	World::World(Dimensionf size) {
		World(size.width, size.height);
	}
	World::World(float width, float height) : Sized(width, height) {
		setTexture(new ColorSquare(Color3f(1, 1, 1)));
	}

	WorldObject** World::getWorldObjects() {
		return worldObjects;
	}

	void World::addWorldObject(WorldObject* worldObject) {
		WorldObject** newList = new WorldObject*[worldObjectCount + 1];
		for (int i = 0; i < worldObjectCount; i++) {
			newList[i] = worldObjects[i];
		}
		newList[worldObjectCount] = worldObject;
		worldObjectCount += 1;
		worldObjects = newList;
	}

	int World::getWorldObjectCount() {
		return worldObjectCount;
	}

	void World::gameTick(double delta) {
		for (int i = 0; i < worldObjectCount; i++) {
			worldObjects[i]->gameTick(delta);
			worldObjects[i]->getTexture()->update(delta);
		}
		checkCollision();
	}
}