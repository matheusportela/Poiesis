#include "bandit/core/math/Circle.h"

Circle::Circle() : center(Vector(0, 0)), r(0.0)
{
}

Circle::Circle(float x, float y) : center(Vector(x, y)), r(0.0)
{
}

Circle::Circle(const Vector& center) : center(center), r(0.0)
{
}

Circle::Circle(float x, float y, float r) : center(Vector(x, y)), r(r)
{
}

Circle::Circle(const Vector& center, float r) : center(center), r(r)
{
}

float Circle::GetR() const
{
    return r;
}

void Circle::SetR(float r)
{
    this->r = r;
}

Vector Circle::GetCenter() const
{
    return center;
}

void Circle::SetCenter(const Vector& center)
{
    this->center = center;
}

void Circle::SetCenterAndRadius(const Vector& center, float r)
{
    this->center = center;
    this->r = r;
}

bool Circle::IsInside(const Vector& vector) const
{
    return (center.CalculateDistance(vector) <= r);
}

bool Circle::Overlaps(const Circle& other) const
{
    float distance = center.CalculateDistance(other.GetCenter());
    float bothRadius = r + other.GetR();
    return (distance <= bothRadius);
}

std::string Circle::ToString() const
{
    char buffer[64];
    sprintf(buffer, "(x: %f, y: %f, r: %f)", center.GetX(), center.GetY(), r);
    std::string stringBuffer = buffer;

    return stringBuffer;
}

std::ostream& operator<<(std::ostream& os, const Circle& circle)
{
    os << circle.ToString();
    return os;
}