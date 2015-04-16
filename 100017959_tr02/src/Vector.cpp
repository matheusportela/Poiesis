// @file   Vector.cpp
// @author Matheus Vieira Portela
// @date   12/04/2015
//
// @brief Vector in 2-dimensional space

#include "Vector.h"

float Vector::GetMagnitude()
{
    return hypot(x, y);
}

float Vector::GetDirection()
{
    return atan2(y, x);
}

void Vector::Multiply(float scalar)
{
    x *= scalar;
    y *= scalar;
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
        std::cerr << "ERROR [Vector] Normalize can only be applied to vectors "
                  << "with non-zero magnitude." << std::endl;
        exit(1);
    }

    float new_x = x/magnitude;
    float new_y = y/magnitude;

    x = new_x;
    y = new_y;
}