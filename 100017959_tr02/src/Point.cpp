// @file   Point.cpp
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Rectangle in 2-dimensional space

#include "Point.h"

Point::Point() : x(0), y(0) {}

Point::Point(float x, float y) : x(x), y(y) {}

Point::Point(Point& other) : x(other.x), y(other.y) {}

float Point::GetX()
{
    return x;
}

void Point::SetX(float x)
{
    this->x = x;
}

float Point::GetY()
{
    return y;
}

void Point::SetY(float y)
{
    this->y = y;
}

void Point::Set(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Point::SetPolar(float r, float ang)
{
    this->x = r*cos(ang);
    this->y = r*sin(ang);
}

void Point::Add(Point& point)
{
    this->x += point.GetX();
    this->y += point.GetY();
}

void Point::Subtract(Point& point)
{
    this->x -= point.GetX();
    this->y -= point.GetY();
}

std::string Point::ToString()
{
    char buffer[64];
    sprintf(buffer, "(x: %f, y: %f)", x, y);
    std::string stringBuffer = buffer;

    return stringBuffer;
}