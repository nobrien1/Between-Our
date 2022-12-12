#pragma once
#include "types.h"

namespace gameEngine {
    class Sized {
        protected:
            Dimensionf size;
            virtual void onSizeChange();
        public:
            Sized();
            Sized(Dimensionf size);
            Sized(float width, float height);
            Dimensionf getSize();
            float getWidth();
            float getHeight();
            void setSize(Dimensionf size);
            void setSize(float width, float height);
            void setWidth(float width);
            void setHeight(float height);
    };
};