#pragma once
#include "WorldObject.h"
#include "types.h"

namespace gameEngine {
    class InteractableWorldObject : public WorldObject {
        private:
            float interactRange = 50;
        public:
            InteractableWorldObject();
            InteractableWorldObject(Pointf position);
            InteractableWorldObject(float x, float y);
            virtual void onInRange();
            virtual void interact();
            void setInteractRange(float r);
            float getInteractRange();
    };
}