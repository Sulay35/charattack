#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include <iostream>

// TODO define global variables
class Vector2
{
public:
    Vector2();
    ~Vector2() = default;
    Vector2(double x, double y);

    double x, y;

    // TODO : constructor Vec2(double mag, double angle)

    Vector2 operator+(Vector2 const &rhs) const;
    Vector2 &operator+=(Vector2 const &rhs);
    Vector2 operator*(double rhs);
    Vector2 operator/(double rhs);
    Vector2 operator*=(double rhs);
    Vector2 operator/=(double rhs);
    Vector2 normalized();
    void setMag(double magnitude);
    void limit(double limit);
    // Rotate the vector using rad angles
    void rotate(double angle);
    double norm() const;
    void add(Vector2 *v2);

    friend std::ostream &operator<<(std::ostream &os, Vector2 &v);
};
