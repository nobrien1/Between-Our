#pragma once
#include "types.h"
#include "Positioned.h"
#include "Texturable.h"
#include "Sized.h"
#include <string>
#include "ui/textGenerator.h"

namespace gameEngine {
    class WorldObject : public Positioned, public Sized, public Texturable {
        private:
            bool collidable = true;
            char* labelText = new char[0];
            Color3f labelColor = Color3f(0.5, 0.5, 0.5);
            text::TextImage label;
            bool checkCollision = false;
            void onPositionChange();
            void onSizeChange();
        public:
            WorldObject();
            WorldObject(Pointf position);
            WorldObject(float x, float y);
            BoundingBox getBoundingBox();
            virtual void gameTick(double delta);
            bool isCollidable();
            void setCollidable(bool c);
            bool shouldCheckCollision();
            void setCheckCollision(bool c);
            text::TextImage getLabel();
            void setLabel(std::string text);
            void setLabel(char* text);
            Color3f getLabelColor();
            void setLabelColor(Color3f color);
    };
};