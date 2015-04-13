// @file   Vector.cpp
// @author Matheus Vieira Portela
// @date   12/04/2015
//
// @brief Vector in 2-dimensional space

#include "Vector.h"

Vector::Vector() : x(0), y(0) {}

Vector::Vector(float x, float y) : x(x), y(y) {}

Vector::Vector(Vector& other) : x(other.x), y(other.y) {}

float Vector::GetX()
{
    return x;
}

void Vector::SetX(float x)
{
    this->x = x;
}

float Vector::GetY()
{
    return y;
}

void Vector::SetY(float y)
{
    this->y = y;
}

void Vector::Set(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vector::SetPolar(float magnitude, float direction)
{
    this->x = magnitude*cos(direction);
    this->y = magnitude*sin(direction);
}

float Vector::GetMagnitude()
{
    return hypot(x, y);
}

float Vector::GetDirection()
{
    return atan2(y, x);
}

void Vector::Add(Vector& vector)
{
    this->x += vector.GetX();
    this->y += vector.GetY();
}

void Vector::Subtract(Vector& vector)
{
    this->x -= vector.GetX();
    this->y -= vector.GetY();
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

std::string Vector::ToString()
{
    char buffer[64];
    sprintf(buffer, "(%f, %f)", x, y);
    std::string stringBuffer = buffer;

    return stringBuffer;
}