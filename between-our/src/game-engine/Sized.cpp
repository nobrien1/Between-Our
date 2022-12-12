#include "Sized.h"
#include "types.h"

namespace gameEngine {
    void Sized::onSizeChange()
    {
    }
    Sized::Sized() {}

    Sized::Sized(Dimensionf size) {
        setSize(size);
    }

    Sized::Sized(float width, float height) {
        setSize(width, height);
    }

    Dimensionf Sized::getSize() {
        return size;
    }

    float Sized::getWidth()
    {
        return size.width;
    }

    float Sized::getHeight()
    {
        return size.height;
    }

    void Sized::setSize(Dimensionf size) {
        setSize(size.width, size.height);
    }

    void Sized::setSize(float width, float height) {
        if (size.width == width && size.height == height) return;

        size.width = width, size.height = height;
        onSizeChange();
    }
    void Sized::setWidth(float width)
    {
        if (size.width == width) return;

        size.width = width;
        onSizeChange();
    }
    void Sized::setHeight(float height)
    {
        if (size.height == height) return;

        size.height = height;
        onSizeChange();
    }
}