#include "InteractableWorldObject.h"
#include "types.h"

namespace gameEngine {
    InteractableWorldObject::InteractableWorldObject() {}
    InteractableWorldObject::InteractableWorldObject(Pointf position) : WorldObject(position) {}
    InteractableWorldObject::InteractableWorldObject(float x, float y) : WorldObject(x, y) {}

    void InteractableWorldObject::onInRange() {}
    void InteractableWorldObject::interact() {}

    void InteractableWorldObject::setInteractRange(float r) {
        interactRange = r;
    }

    float InteractableWorldObject::getInteractRange() {
        return interactRange;
    }
}