#include "WorldObject.h"
#include "types.h"
#include "Positioned.h"
#include <iostream>
#include <string>

namespace gameEngine {
    void WorldObject::onPositionChange()
    {
        checkCollision = true;
    }
    void WorldObject::onSizeChange()
    {
        checkCollision = true;
    }
    WorldObject::WorldObject() {}
    WorldObject::WorldObject(Pointf position) : Positioned(position) {}
    WorldObject::WorldObject(float x, float y) : Positioned(x, y) {}
    BoundingBox WorldObject::getBoundingBox()
    {
        return BoundingBox(position, size);
    }
    void WorldObject::gameTick(double delta) {
        
    }
    bool WorldObject::isCollidable()
    {
        return collidable;
    }
    void WorldObject::setCollidable(bool c)
    {
        collidable = c;
    }
    bool WorldObject::shouldCheckCollision()
    {
        return checkCollision && collidable;
    }
    void WorldObject::setCheckCollision(bool c)
    {
        checkCollision = c;
    }
    text::TextImage WorldObject::getLabel()
    {
        return label;
    }
    void WorldObject::setLabel(std::string text)
    {
        labelText = &text[0];
        label = gameEngine::text::getTextImage(&text[0], 15);
    }
    void WorldObject::setLabel(char* text)
    {
        labelText = text;
        label = gameEngine::text::getTextImage(text, 15);
    }
    Color3f WorldObject::getLabelColor()
    {
        return labelColor;
    }
    void WorldObject::setLabelColor(Color3f color)
    {
        labelColor = color;
    }
}