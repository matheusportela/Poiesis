// @file   Vector.cpp
// @author Matheus Vieira Portela
// @date   12/04/2015
//
// @brief Vector in 2-dimensional space

#include "Vector.h"

Vector::Vector() : Point()
{
}

Vector::Vector(float x, float y) : Point(x, y)
{
}

Vector::Vector(const Point& point) : Point(point)
{
}

float Vector::GetMagnitude() const
{
    return hypot(x, y);
}

float Vector::GetDirection() const
{
    return atan2(y, x);
}

void Vector::Rotate(float angle)
{
    float new_x = x*cos(angle) - y*sin(angle);
    float new_y = x*sin(angle) + y*cos(angle);

    x = new_x;
    y = new_y;
}

void Vector::Normalize()
{
    float magnitude = GetMagnitude();

    if (magnitude == 0)
    {
        LOG_E("[Vector] Normalize can only be applied to vectors with non-zero "
            << "magnitude.");
        exit(1);
    }

    float new_x = x/magnitude;
    float new_y = y/magnitude;

    x = new_x;
    y = new_y;
}

void Vector::Saturate(float maximum)
{
    if (GetMagnitude() > maximum)
    {
        Normalize();
        Multiply(maximum);
    }
}