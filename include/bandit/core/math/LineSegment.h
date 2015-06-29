// Line segment in 2-dimensional space.

#ifndef LINE_SEGMENT_H_
#define LINE_SEGMENT_H_

#include <string>

#include "bandit/core/math/Vector.h"

class LineSegment
{
  public:
    // Empty constructor.
    LineSegment();

    // Initialize with pre-defined (x, y) begin coordinates, zero direction,
    // and zero size.
    LineSegment(float x, float y);
    LineSegment(const Vector& begin);

    // Initialize with pre-defined (x, y) begin and end coordinates.
    LineSegment(float xBegin, float yBegin, float xEnd, float yEnd);
    LineSegment(const Vector& begin, const Vector& end);
    
    // Gets direction, in radians.
    float GetDirection() const;

    // Gets and sets size.
    float GetSize() const;

    // Sets size and direction, in radians. Begin coordinates remains the same,
    // changing only the end coordinates.
    void SetSizeAndDirection(float size, float direction);

    // Gets begin and end coordinates.
    Vector GetBegin() const;
    Vector GetEnd() const;

    // Returns string with circle's coordinates and radius.
    std::string ToString() const;

  private:
    // 2-D (x, y) coordinates corresponding to the line's begin.
    Vector begin;

    // 2-D (x, y) coordinates corresponding to the line's end.
    Vector end;
};

std::ostream& operator<<(std::ostream& os, const LineSegment& lineSegment);

#endif // LINE_SEGMENT_H_