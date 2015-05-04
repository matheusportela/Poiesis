// @file   Rect.cpp
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Rectangle in 2-dimensional space

#include "Rect.h"

Rect::Rect() : point(0, 0), w(0), h(0) {}

Rect::Rect(const Point& point) : point(point), w(0), h(0) {}

Rect::Rect(const Point& point, float w, float h) : point(point), w(w), h(h) {}

Point Rect::GetPoint() const
{
    return point;
}

void Rect::SetPoint(const Point& point)
{
    this->point = point;
}

float Rect::GetW() const
{
    return w;
}

void Rect::SetW(float w)
{
    this->w = w;
}

float Rect::GetH() const
{
    return h;
}

void Rect::SetH(float h)
{
    this->h = h;
}

void Rect::Set(const Point& point)
{
    this->point = point;
}

void Rect::Set(const Point& point, float w, float h)
{
    this->point = point;
    this->w = w;
    this->h = h;
}

void Rect::SetCenter(const Point& centerPoint, float w, float h)
{
    this->point.SetX(centerPoint.GetX() - w/2.0);
    this->point.SetY(centerPoint.GetY() - h/2.0);
    this->w = w;
    this->h = h;
}

Point Rect::GetCenter() const
{
    Point centerPoint;
    centerPoint.SetX(point.GetX() + w/2.0);
    centerPoint.SetY(point.GetY() + h/2.0);
    return centerPoint;
}

std::string Rect::ToString() const
{
    char buffer[64];
    sprintf(buffer, "(x: %f, y: %f, w: %f, h: %f)", point.GetX(), point.GetY(), w, h);
    std::string stringBuffer = buffer;

    return stringBuffer;
}

bool Rect::IsInside(const Point& point) const
{
    return (point.GetX() >= this->point.GetX() and point.GetX() <= this->point.GetX() + w and
            point.GetY() >= this->point.GetY() and point.GetY() <= this->point.GetY() + h);
}