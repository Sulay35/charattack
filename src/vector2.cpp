#pragma once

#include "vector2.hpp"

// TODO define global variables
Vector2::Vector2()
    : x(0.0f), y(0.0f)
{
}
Vector2::Vector2(double x, double y) : x(x), y(y) { }

// TODO : constructor Vec2(double mag, double angle)

Vector2 Vector2::operator+(Vector2 const &rhs) const
{
    return Vector2(x + rhs.x, y + rhs.y);
}
Vector2 &Vector2::operator+=(Vector2 const &rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}
Vector2 Vector2::operator*(double rhs)
{
    return Vector2(x * rhs, y * rhs);
}

Vector2 Vector2::operator/(double rhs)
{
    return Vector2(x / rhs, y / rhs);
}

Vector2 Vector2::operator*=(double rhs)
{
    return Vector2(x * rhs, y * rhs);
}

Vector2 Vector2::operator/=(double rhs)
{
    return Vector2(x / rhs, y / rhs);
}

Vector2 Vector2::normalized()
{
    Vector2 normalized = (*this) / norm();
    // printf("\tf_normalized = %f \n",normalized.norm());
    return normalized;
}

void Vector2::setMag(double magnitude)
{
    if (magnitude != 0.0f)
        *this = this->normalized() * magnitude;
    // printf("\t%f\tf = %f \n",magnitude, this->norm());
}

void Vector2::limit(double limit)
{
    if (this->norm() > limit)
    {
        setMag(limit);
    }
}

// Rotate the vector using rad angles
void Vector2::rotate(double angle)
{
    double x2 = x * cos(angle) - y * sin(angle);
    double y2 = x * sin(angle) + y * cos(angle);
    x = x2;
    y = y2;
}

double Vector2::norm() const
{
    return sqrt(x * x + y * y);
}

void Vector2::add(Vector2 *v2)
{
    x += v2->x;
    y += v2->y;
}

std::ostream &operator<<(std::ostream &os, Vector2 &v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}