#pragma once
#include "Sized.h"
#include "WorldObject.h"
#include "types.h"
#include "Texturable.h"

namespace gameEngine {
	class World : public Sized, public Texturable {
		private:
			WorldObject** worldObjects = {};
			int worldObjectCount = 0;
			void checkCollision();
		public:
			World(Dimensionf size);
			World(float width, float height);
			WorldObject** getWorldObjects();
			void addWorldObject(WorldObject* worldObject);
			int getWorldObjectCount();
			void gameTick(double delta);
	};
}

