#pragma once
#include <string>
#include "vector2.hpp"

class BoxCollider {
public:
    BoxCollider() = default;
    BoxCollider(double width, double height, std::string tag);

    inline double getWidth() const { return w; }
    inline double getHeight() const { return h; }
    inline Vector2 getPos() const { return pos; }
    void updatePos(Vector2 newPos);

    std::string getTag() const { return tag; }


private:
    double w,h;
    Vector2 pos; // How to update this ? callback
    std::string tag;
};
