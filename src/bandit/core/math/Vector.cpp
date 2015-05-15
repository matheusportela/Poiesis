#include "bandit/core/math/Vector.h"

Vector::Vector() : x(0), y(0) {}

Vector::Vector(float x, float y) : x(x), y(y) {}

Vector::Vector(const Vector& other) : x(other.x), y(other.y) {}

float Vector::GetX() const
{
    return x;
}

void Vector::SetX(float x)
{
    this->x = x;
}

float Vector::GetY() const
{
    return y;
}

void Vector::SetY(float y)
{
    this->y = y;
}

float Vector::GetMagnitude() const
{
    return hypot(x, y);
}

float Vector::GetDirection() const
{
    return atan2(y, x);
}

void Vector::Set(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vector::Set(Vector vector)
{
    this->x = vector.x;
    this->y = vector.y;
}

void Vector::SetPolar(float magnitude, float direction)
{
    this->x = magnitude*cos(direction);
    this->y = magnitude*sin(direction);
}

void Vector::Add(Vector vector)
{
    this->x += vector.GetX();
    this->y += vector.GetY();
}

void Vector::Subtract(Vector vector)
{
    this->x -= vector.GetX();
    this->y -= vector.GetY();
}

void Vector::Multiply(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
}

void Vector::Divide(float scalar)
{
    if (scalar == 0.0)
    {
        LOG_E("[Vector] Division by zero");
        exit(1);
    }

    this->x /= scalar;
    this->y /= scalar;
}

void Vector::Negate()
{
    Multiply(-1);
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

float Vector::CalculateDistance(Vector vector) const
{
    return hypot(vector.x - x, vector.y - y);
}

std::string Vector::ToString() const
{
    char buffer[64];
    sprintf(buffer, "(%f, %f)", x, y);
    std::string stringBuffer = buffer;

    return stringBuffer;
}