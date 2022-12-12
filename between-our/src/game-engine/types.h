#pragma once

namespace gameEngine {
    /*template<typename T> struct Point {
        T x, y;
        Point();
        Point(T x, T y);
    };
    using Pointf = Point<float>;*/
    struct Pointf {
        float x, y;
        Pointf();
        Pointf(float x, float y);
    };
    struct Dimensionf {
        float width, height;
        Dimensionf();
        Dimensionf(float width, float height);
    };
    struct Dimensioni {
        int width, height;
        Dimensioni();
        Dimensioni(int width, int height);
    };
    struct Vectorf {
        float x, y;
        Vectorf();
        Vectorf(float x, float y);
    };
    struct Color3f {
        float r, g, b;
        Color3f();
        Color3f(float r, float g, float b);
    };
    struct BoundingBox {
        float top, bottom, left, right;
        BoundingBox();
        BoundingBox(float left, float right, float top, float bottom);
        BoundingBox(Pointf origin, Dimensionf size);
    };
};