#include "boxCollider.hpp"

BoxCollider::BoxCollider(double width, double height, std::string tag) : w(width), h(height), tag(tag) {};

void BoxCollider::updatePos(Vector2 newPos) {
    pos = Vector2(newPos);
}