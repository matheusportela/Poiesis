#include "bandit/core/math/LineSegment.h"

LineSegment::LineSegment()
{
}

LineSegment::LineSegment(float x, float y) :
    begin(Vector(x, y)), end(Vector(x, y))
{
}

LineSegment::LineSegment(const Vector& begin) :
    begin(begin), end(begin)
{
}

LineSegment::LineSegment(float xBegin, float yBegin, float xEnd, float yEnd) :
    begin(Vector(xBegin, yBegin)), end(Vector(xEnd, yEnd))
{
}

LineSegment::LineSegment(const Vector& begin, const Vector& end) :
    begin(begin), end(end)
{
}

float LineSegment::GetDirection() const
{
    float dx = end.GetX() - begin.GetX();
    float dy = end.GetY() - begin.GetY();
    return atan2(dy, dx);
}

float LineSegment::GetSize() const
{
    float dx = end.GetX() - begin.GetX();
    float dy = end.GetY() - begin.GetY();
    return hypot(dx, dy);
}

void LineSegment::SetSizeAndDirection(float size, float direction)
{
    float dx = size*cos(direction);
    float dy = size*sin(direction);

    float x = begin.GetX() + dx;
    float y = begin.GetY() + dy;

    end = Vector(x, y);
}

Vector LineSegment::GetBegin() const
{
    return begin;
}

Vector LineSegment::GetEnd() const
{
    return end;
}

std::string LineSegment::ToString() const
{
    char buffer[64];
    sprintf(buffer, "(x: %f, y: %f) -> (x: %f, y: %f)", begin.GetX(), begin.GetY(),
        end.GetX(), end.GetY());
    std::string stringBuffer = buffer;

    return stringBuffer;
}

std::ostream& operator<<(std::ostream& os, const LineSegment& lineSegment)
{
    os << lineSegment.ToString();
    return os;
}